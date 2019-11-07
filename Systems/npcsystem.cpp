#include "npcsystem.h"
#include "World.h"
#include "Components/npc.h"
#include "Components/transform.h"
#include "bsplinecurve.h"

NpcSystem::NpcSystem()
{

}


void NpcSystem::beginPlay()
{
}

void NpcSystem::tick()
{
    for(const auto& entity : entities_)
    {
        auto npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);

        if(!npc) continue;
        if(!npc->bSplineCurve) continue;

        npc->state_ = NPCstates::PATROL;
        switch (npc->state_) {
        case NPCstates::PATROL:
            patrol(entity, npc);
            break;
        default:
            break;
        }
    }
}

void NpcSystem::endPlay()
{
}

void NpcSystem::patrol(Entity entity, Npc* npc)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if(!transform) return;

    currentT_ += npc->speed_/60;
    if(currentT_ > 0.0001f && currentT_ < 1.f)
        transform->position_ = npc->bSplineCurve->curvePosition(currentT_);
    else
    {
        npc->event = NPCevents::ENDPOINT_ARRIVED;
        notify(entity);
    }

}

void NpcSystem::notify(Entity entity, std::optional<unsigned int> index)
{
    auto npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
    if(!npc) return;

    switch (npc->event) {
    case NPCevents::ITEM_TAKEN:
        if(index.has_value())
            npc->bSplineCurve->removeControlPoint(index.value() + 1);
        break;
    case NPCevents::ENDPOINT_ARRIVED:
       // npc->bSplineCurve->randomizeControlpoints();
        npc->speed_ = -npc->speed_;
        break;
    default:
        break;
    }
}

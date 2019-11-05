#include "npcsystem.h"
#include "World.h"
#include "Components/npc.h"
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

        switch (npc->state) {
        case NPCstates::PATROL:
            patrol(npc);
            break;
        default:
            break;
        }
    }
}

void NpcSystem::endPlay()
{
}

void NpcSystem::patrol(Npc* npc)
{
    currentT_ += npc->speed_/60;
    if(currentT_ < 0.01f || currentT_ > 1.f)
        npc->bSplineCurve->curvePosition(currentT_);

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
        npc->bSplineCurve->randomizeControlpoints();
        npc->speed_ = -npc->speed_;
        break;
    default:
        break;
    }
}

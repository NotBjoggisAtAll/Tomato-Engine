#include "npcsystem.h"
#include "world.h"
#include "Components/npc.h"
#include "Components/transform.h"
#include "bsplinecurve.h"

void NpcSystem::tick(float /*deltaTime*/)
{
    for(const auto& entity : entities_)
    {
        auto npc = getWorld()->getComponent<Npc>(entity).value();

        if(!npc->bSplineCurve) continue;

        npc->state_ = NPCstates::PATROL;

        switch (npc->state_)
        {
        case NPCstates::PATROL:
            patrol(entity, npc);
            break;
        default:
            break;
        }
    }
}

void NpcSystem::patrol(Entity entity, Npc* npc)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if(!transform) return;

    npc->currentT_ += npc->speed_/60;
    if(npc->currentT_ > 0.0001f && npc->currentT_ < 1.f)
    {
        transform->position_ = npc->bSplineCurve->curvePosition(npc->currentT_);
    }
    else
    {
        npc->event_ = NPCevents::ENDPOINT_ARRIVED;
        notify(entity);
    }
}

void NpcSystem::notify(Entity entity)
{
    auto npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
    if(!npc) return;

    switch (npc->event_)
    {
    case NPCevents::ENDPOINT_ARRIVED:
        getWorld()->destroyEntityLater(entity);
        break;
    default:
        break;
    }
}

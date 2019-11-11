#ifndef NPC_H
#define NPC_H

#include "component.h"
#include "types.h"

class BSplineCurve;

enum class NPCstates {SLEEP = 0, PATROL, LEARN, CHASE};
enum class NPCevents {ENDPOINT_ARRIVED = 0, ITEM_TAKEN, PLAYER_DETECTED, OBSTACLE_DETECTED};

struct Npc : public Component
{
    Npc();
    Npc(BSplineCurve* Curve);
    BSplineCurve* bSplineCurve = nullptr;

    NPCevents event;
    NPCstates state_;
    float speed_ = 0.1f;
    float currentT_ = 0;

    virtual QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // NPC_H

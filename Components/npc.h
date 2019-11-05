#ifndef NPC_H
#define NPC_H

#include "GSL/vector3d.h"

class BSplineCurve;

enum class NPCstates {SLEEP = 0, PATROL, LEARN, CHASE};
enum class NPCevents {ENDPOINT_ARRIVED = 0, ITEM_TAKEN, PLAYER_DETECTED, OBSTACLE_DETECTED};

struct Npc
{
    Npc();
    Npc(BSplineCurve* Curve);
    BSplineCurve* bSplineCurve;

    NPCstates state;
    NPCevents event;
    float speed_ = 0.1f;

};

#endif // NPC_H

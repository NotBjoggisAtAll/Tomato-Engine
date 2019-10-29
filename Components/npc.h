#ifndef NPC_H
#define NPC_H

#include "GSL/vector3d.h"
#include <queue>

class BSplineCurve;

enum class NPCstates {SLEEP = 0, PATROL, LEARN, CHASE};
enum class NPCevents {ENDPOINT_ARRIVED = 0, ITEM_TAKEN, PLAYER_DETECTED, OBSTACLE_DETECTED};

class Npc
{
public:
    Npc();
    void patrol();
    void learn();
private:
    BSplineCurve& bSplineCurve;
    gsl::Vector3D player;
    NPCstates state;
    NPCevents event;
    void notify(int notification);
    std::queue<int> notification_queue;

    float elapsed_time;
    //B-spline kurven har en skjøtvektor, f.eks {0,0,0,1,2,3,3,3}
    //elapsed_time er en parameter
    // 0 <= elapsed_time <= 3 i dette tilfellet
    void build_path();
    // Lage en (ny) bare for tatruljering
    // gjøre en permutasjon av kontrollpunktene (items, ikke endepunkter)
    // viktig å ikke endre enepunktene

    gsl::Vector3D position;
};

#endif // NPC_H

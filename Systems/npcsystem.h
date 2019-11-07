#ifndef NPCSYSTEM_H
#define NPCSYSTEM_H

#include "Systems/system.h"

class Npc;
class NpcSystem : public System
{
public:
    NpcSystem();

    // System interface
public:
    void beginPlay() override;
    void tick() override;
    void endPlay() override;


    void patrol(Entity entity, Npc *npc);
    void learn();
    void notify(Entity entity, std::optional<unsigned int> index = std::nullopt);

    float elapsed_time;
    //B-spline kurven har en skjøtvektor, f.eks {0,0,0,1,2,3,3,3}
    //elapsed_time er en parameter
    // 0 <= elapsed_time <= 3 i dette tilfellet
    void build_path();
    // Lage en (ny) bare for tatruljering
    // gjøre en permutasjon av kontrollpunktene (items, ikke endepunkter)
    // viktig å ikke endre enepunktene

    /// Stores the current position on the BSpline (from 0 to 1)
    float currentT_ = 0;

    /// If true the currentT increments when curvePosition() is called.
    /// Otherwise the currentT decrements.
    bool bIncrementT = true;
private:
    float getHeightBaryc(Entity npc, Entity terrain);
};

#endif // NPCSYSTEM_H

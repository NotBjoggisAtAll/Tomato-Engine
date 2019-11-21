#ifndef NPCSYSTEM_H
#define NPCSYSTEM_H

#include "Systems/system.h"
#include "GSL/vector3d.h"
#include <queue>

struct Npc;
class NpcSystem : public System
{
public:
    NpcSystem();

    // System interface
public:
    void beginPlay() override;
    void tick(float deltaTime) override;
    void endPlay() override;


    void patrol(Entity entity, Npc *npc);
    void learn();
    void notify(Entity entity);
};

#endif // NPCSYSTEM_H

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include "system.h"

class ProjectileSystem : public System
{
public:
    ProjectileSystem();
    void beginPlay() override;
    void tick() override;
    void endPlay() override;
};

#endif // PROJECTILESYSTEM_H

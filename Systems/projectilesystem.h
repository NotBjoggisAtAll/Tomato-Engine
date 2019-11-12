#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include "system.h"
#include <queue>

class ProjectileSystem : public System
{
public:
    ProjectileSystem();
    void beginPlay() override;
    void tick(float deltaTime) override;
    void endPlay() override;

private:

    std::queue<Entity> entitiesToBeDeleted_;
};

#endif // PROJECTILESYSTEM_H

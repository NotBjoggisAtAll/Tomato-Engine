#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include "system.h"
#include <queue>

/**
 * The ProjectileSystem calculates the direction and moves the Projectiles in the world.
 */
class ProjectileSystem : public System
{
public:
    /**
     * Default constructor.
     */
    ProjectileSystem() = default;

    /**
     * Tick runs every frame.
     * Calculate a direction based on the nearest Npc. Moves the Projectile at a constant speed that direction.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    void tick(float deltaTime) override;

private:

    /// The queue contains projectiles that should be deleted based on their lifespan.
    std::queue<Entity> entitiesToBeDeleted_;
};

#endif // PROJECTILESYSTEM_H

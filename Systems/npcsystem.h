#ifndef NPCSYSTEM_H
#define NPCSYSTEM_H

#include "Systems/system.h"
#include "GSL/vector3d.h"

struct Npc;

/**
 * The NpcSystem responsibility is to update the Npc entity behaviour.
 * It's used to move the Npc along a BSplineCurve.
 */
struct NpcSystem : public System
{
    /**
     * Default constructor.
     */
    NpcSystem() = default;

    /**
     * Tick runs every frame.
     * Check which state the Npc is in and runs the correct function.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    void tick(float deltaTime) override;

    /**
     * Updates the Npc's position based on it's current location on the BSpline.
     * @param entity - The Npc Entity.
     * @param npc - The Npc component.
     */
    void patrol(Entity entity, Npc *npc);

    /**
     * Called whenever the Npc should react to an event.
     * @param entity
     */
    void notify(Entity entity);
};

#endif // NPCSYSTEM_H

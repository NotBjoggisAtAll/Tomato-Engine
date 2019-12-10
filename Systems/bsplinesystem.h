#ifndef BSPLINESYSTEM_H
#define BSPLINESYSTEM_H

#include "Systems/system.h"

/**
 * The BSplineSystem updates the BSpline Mesh (The lines drawn) whenever they changes.
 */
class BSplineSystem : public System
{
public:
    /**
     * Default constructor.
     */
    BSplineSystem() = default;

    /**
     * Tick runs every frame.
     * The BSplineSystem updates the BSpline Mesh (The lines drawn) whenever they changes.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    virtual void tick(float deltaTime) override;
};

#endif // BSPLINESYSTEM_H

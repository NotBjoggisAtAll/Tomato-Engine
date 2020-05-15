#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "system.h"

struct Camera;

/**
 * Updates the cameras viewmatrix and position.
 */
class CameraSystem : public System
{
public:
    /**
     * Default constructor.
     */
    CameraSystem() = default;

    /**
     * Tick runs every frame.
     * Updates the cameras viewmatrix and position.
     * Only updates the position to the Camera in use.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    virtual void tick(float deltaTime) override;

private:

    /**
     * Calculates the new Camera frustum.
     * @param camera - Camera component.
     */
    void updateFrustum(Camera *camera);
};

#endif // CAMERASYSTEM_H

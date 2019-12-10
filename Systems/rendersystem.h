#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"
#include "GSL/vector3d.h"

/**
 * The RenderSystem is responsible to render objects to the screen.
 */
class RenderSystem : public QOpenGLFunctions_4_1_Core, public System
{
public:
    /**
     * Default constructor.
     */
    RenderSystem() = default;

    /**
     * Tick runs every frame.
     * Renders all Mesh components based on the Transform.
     * Only renders stuff inside the frustum unless if it's specified on the Mesh component that it always should be rendered.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    void tick(float) override;

    /// The total vertices count. Displayed on the statusbar.
    unsigned int totalVerticeCount_ = 0;
private:

    /**
     * Checks if the Mesh is inside the frustum or not.
     * Puts a sphere with the specified radius around the object's Transform.
     * Returns whether the sphere is inside or outside the frustum.
     * @param vecCenter - The object's position.
     * @param radius - The sphere radius.
     * @return true if it's inside the frustum. Otherwise returns false.
     */
    bool sphereInsideFrustum(const gsl::Vector3D vecCenter, float radius);
};

#endif // RENDERSYSTEM_H

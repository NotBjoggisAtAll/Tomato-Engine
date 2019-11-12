#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"
#include "GSL/vector3d.h"

struct RenderSystem : public QOpenGLFunctions_4_1_Core, public System
{

    RenderSystem() = default;

     void beginPlay() override;
     void tick(float deltaTime) override;
     int totalVerticeCount = 0;
private:
    bool sphereInsideFrustum(const gsl::Vector3D vecCenter, float radius);

};

#endif // RENDERSYSTEM_H

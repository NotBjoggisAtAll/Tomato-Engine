#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>
#include "system.h"
#include "GSL/vector3d.h"

class RenderSystem : public QOpenGLFunctions_4_1_Core, public System
{
public:
    RenderSystem() = default;

     void beginPlay() override;
     void tick(float) override;
     unsigned int totalVerticeCount_ = 0;
private:
    bool sphereInsideFrustum(const gsl::Vector3D vecCenter, float radius);
};

#endif // RENDERSYSTEM_H

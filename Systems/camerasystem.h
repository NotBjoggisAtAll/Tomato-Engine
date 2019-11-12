#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "system.h"

class Camera;

class CameraSystem : public System
{
public:
    CameraSystem();
    virtual void beginPlay() override;
    virtual void tick(float deltaTime) override;
    virtual void endPlay() override;
private:
    void updateFrustum(Camera *camera);
};

#endif // CAMERASYSTEM_H

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "Systems/system.h"
#include <memory>
#include "GSL/vector3d.h"

class EventHandler;

class InputSystem : public System
{
public:
    InputSystem();
    void beginPlay() override;
    void tick() override;
    void endPlay() override;

    void setEventHandler(const std::shared_ptr<EventHandler> &eventHandler);

private:
    std::shared_ptr<EventHandler> eventHandler_;
    void addPosition(Entity entity, gsl::Vector3D translation);

    float cameraSpeed = 0.01f;

};

#endif // INPUTSYSTEM_H

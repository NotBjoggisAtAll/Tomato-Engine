#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "Systems/system.h"
#include "GSL/vector3d.h"
#include <memory>

class EventHandler;

/**
 * Responsible to move the camera and other objects with the Input component.
 */
class InputSystem : public System
{
public:
    /**
     * Default constructor.
     */
    InputSystem() = default;

    /**
     * Tick runs every frame.
     * Checks what keys was pressed and moves object's based on that.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    void tick(float deltaTime) override;

    /**
     * Setter for the EventHandler.
     * @param eventHandler
     */
    void setEventHandler(const std::shared_ptr<EventHandler> &eventHandler);

private:

    /**
     * Translates the entity's position based on the parameter.
     * @param entity - Entity
     * @param translation - gsl::Vecto3D.
     */
    void addPosition(Entity entity, gsl::Vector3D translation);

    /// Pointer to the EventHandler.
    std::shared_ptr<EventHandler> eventHandler_;

    /// The camera speed.
    float cameraSpeed = 0.01f;
};

#endif // INPUTSYSTEM_H

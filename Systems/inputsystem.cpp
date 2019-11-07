#include "inputsystem.h"
#include "eventhandler.h"
#include "world.h"
#include "Components/transform.h"
#include "Components/input.h"
#include "camera.h"

InputSystem::InputSystem()
{

}


void InputSystem::beginPlay()
{
}

void InputSystem::tick()
{
    auto camera = getWorld()->getCurrentCamera();

    camera->moveForward(0.f);  //cancel last frame movement
    if(eventHandler_->keys_[Qt::MouseButton::RightButton] == true)
    {
        if(eventHandler_->keys_[Qt::Key_W] == true)
            camera->moveForward(-cameraSpeed);
        if(eventHandler_->keys_[Qt::Key_S] == true)
            camera->moveForward(cameraSpeed);
        if(eventHandler_->keys_[Qt::Key_D] == true)
            camera->moveRight(cameraSpeed);
        if(eventHandler_->keys_[Qt::Key_A] == true)
            camera->moveRight(-cameraSpeed);
        if(eventHandler_->keys_[Qt::Key_Q] == true)
            camera->moveUp(-cameraSpeed);
        if(eventHandler_->keys_[Qt::Key_E] == true)
            camera->moveUp(cameraSpeed);
    }else{
        if(!getWorld()->bGameRunning) return;
        for(const auto& entity : entities_)
        {
            auto input = getWorld()->getComponent<Input>(entity).value();
            if(!input->isControllable) continue;

            if(eventHandler_->keys_[Qt::Key_W] == true)
                addPosition(entity,{0,0,0.1f});
            if(eventHandler_->keys_[Qt::Key_S] == true)
                addPosition(entity,{0,0,-0.1f});
            if(eventHandler_->keys_[Qt::Key_D] == true)
                addPosition(entity,{-0.1f,0,0});
            if(eventHandler_->keys_[Qt::Key_A] == true)
                addPosition(entity,{0.1f,0,0});
        }
    }
}

void InputSystem::endPlay()
{
}

void InputSystem::setEventHandler(const std::shared_ptr<EventHandler> &eventHandler)
{
    eventHandler_ = eventHandler;
}

void InputSystem::addPosition(Entity entity, gsl::Vector3D translation)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if (!transform) return;

    auto position = transform->position_;
    transform->position_ = position + translation;
}

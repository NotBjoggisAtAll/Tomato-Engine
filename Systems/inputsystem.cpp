#include "inputsystem.h"
#include "eventhandler.h"
#include "world.h"
#include "Components/transform.h"
#include "Components/input.h"
#include "Components/camera.h"

void InputSystem::beginPlay()
{
}

void InputSystem::tick(float deltaTime)
{
    auto cameraEntity = getWorld()->getCurrentCamera();
    if(cameraEntity == -1) return;

    auto camera = getWorld()->getComponent<Camera>(cameraEntity).value_or(nullptr);
    if(!camera) return;
    camera->speed_ = 0.f;  //cancel last frame movement
    if(eventHandler_->keys_[Qt::MouseButton::RightButton] == true)
    {
        if(getWorld()->bGameRunning) return;
        auto transform = getWorld()->getComponent<Transform>(cameraEntity).value_or(nullptr);
        if(!transform) return;
        if(eventHandler_->keys_[Qt::Key_W] == true)
            camera->speed_ = -cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_S] == true)
            camera->speed_ = cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_D] == true)
            transform->position_ += camera->right_ * cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_A] == true)
            transform->position_ += camera->right_ * -cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_Q] == true)
            transform->position_.y += -cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_E] == true)
            transform->position_.y += cameraSpeed;
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

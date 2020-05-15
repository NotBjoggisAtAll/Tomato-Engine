#include "inputsystem.h"
#include "eventhandler.h"
#include "world.h"
#include "Components/transform.h"
#include "Components/input.h"
#include "Components/camera.h"
#include "Factories/resourcefactory.h"
#include "Managers/shadermanager.h"
#include "Systems/soundsystem.h"
#include "Components/material.h"
#include "Managers/soundmanager.h"
#include "Components/projectile.h"

void InputSystem::beginPlay()
{
    for (int i = 0; i < 100; ++i)
    {
        Projectile proj;

        proj.direction_ = gsl::Vector3D(0,0,1);

        Entity pro = getWorld()->createEntity();
        getWorld()->addComponent(pro, Transform({1000,0,0},{},{0.1f,0.1f,0.1f}));
        getWorld()->addComponent(pro, ResourceFactory::get()->loadMesh("box2.txt"));
        getWorld()->addComponent(pro, ResourceFactory::get()->getCollision("box2.txt"));
        getWorld()->addComponent(pro, Material(ShaderManager::get()->phongShader(),gsl::Vector3D(0,0,0)));
        getWorld()->addComponent(pro, Sound(SoundManager::instance()->createSource("shoot", "laser.wav",false, 0.4f),false));
        getWorld()->addComponent(pro, proj);
        bullets_.push(pro);
    }
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
    }
    else
    {
        if(!getWorld()->bGameRunning) return;

        shootTimer_ += deltaTime;

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

            if(eventHandler_->keys_[Qt::Key_Space] == true)
                shoot(entity);
        }
    }
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

void InputSystem::shoot(Entity entity)
{
    if(shootTimer_ > 0.1f)
    {
        shootTimer_ = 0;
        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        if(!transform) return;

        Entity bullet = bullets_.front();
        bullets_.pop();

        auto bulletTransform = getWorld()->getComponent<Transform>(bullet).value_or(nullptr);
        auto bulletProjectile = getWorld()->getComponent<Projectile>(bullet).value_or(nullptr);
        auto bulletAudio = getWorld()->getComponent<Sound>(bullet).value_or(nullptr);

        qDebug() << bullet;

        bulletTransform->position_  = transform->position_;
        bulletProjectile->active_ = true;
        getWorld()->getSystem<SoundSystem>()->playSound(bulletAudio);

        bullets_.push(bullet);


    }
}

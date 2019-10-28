#include "movementsystem.h"
#include "world.h"
#include "Components/transform.h"
#include "Components/entitydata.h"
#include "Components/collision.h"
#include "GSL/matrix4x4.h"

void MovementSystem::addPosition(Entity entity, gsl::Vector3D translation)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if (!transform) return;

    auto position = transform->position_;
    transform->position_ = position + translation;

    for(auto& child : getWorld()->getComponent<EntityData>(entity).value_or(nullptr)->children_)
    {
        addPosition(child,translation);
    }
}

void MovementSystem::setPosition(Entity entity, gsl::Vector3D position)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if (!transform) return;

    transform->position_ = position;

    for(auto& child : getWorld()->getComponent<EntityData>(entity).value_or(nullptr)->children_)
    {
        setPosition(child,position);
    }
}

void MovementSystem::setScale(Entity entity, gsl::Vector3D scale)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    auto collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);

    if (!transform) return;

    transform->scale_ = scale;

    if(!collision) return;

    gsl::Matrix4x4 tempMatrix;
    tempMatrix.scale(transform->scale_);

    collision->scaledMaxVector_ = (tempMatrix * gsl::Vector4D(collision->maxVector_,0)).getXYZ();
    collision->scaledMinVector_ = (tempMatrix * gsl::Vector4D(collision->minVector_,0)).getXYZ();

    for(auto& child : getWorld()->getComponent<EntityData>(entity).value_or(nullptr)->children_)
    {
        setScale(child,scale);
    }
}

#include "movementsystem.h"
#include "World.h"
#include "Components/transformcomponent.h"
#include "Components/entitydata.h"

MovementSystem::MovementSystem()
{
}

void MovementSystem::addPosition(Entity entity, gsl::Vector3D translation)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);

    auto position = transform->position;
    transform->position = position + translation;

    for(auto& child : getWorld()->getComponent<EntityData>(entity).value_or(nullptr)->children)
    {
        addPosition(child,translation);
    }
}

void MovementSystem::setPosition(Entity entity, gsl::Vector3D position)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);

    transform->position = position;

    for(auto& child : getWorld()->getComponent<EntityData>(entity).value_or(nullptr)->children)
    {
        setPosition(child,position);
    }
}

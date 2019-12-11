#include "world.h"

World* World::instance = nullptr;

Entity World::createEntity()
{
    auto eId = entityManager_->createEntity();
    return eId;
}

void World::destroyEntityLater(Entity entity)
{
    entitiesToDelete_.push(entity);
}

void World::destroyEntities()
{
    if(entitiesToDelete_.empty())
        return;

    while(!entitiesToDelete_.empty())
    {
        entityManager_->destroyEntity(entitiesToDelete_.front());
        componentManager_->entityDestroyed(entitiesToDelete_.front());
        systemManager_->entityDestroyed(entitiesToDelete_.front());
        entitiesToDelete_.pop();
    }
    emit updateWorldOutliner();
}

std::vector<Entity> World::getEntities()
{
    return entityManager_->getEntities();
}

std::unordered_map<std::string, ComponentType> World::getComponentTypes()
{
    return componentManager_->getComponentTypes();
}

Entity World::getCurrentCamera()
{
    return currentCamera_;
}

void World::setCurrentCamera(Entity newCamera)
{
    currentCamera_ = newCamera;
    emit updateCameraPerspectives();
}

World::World()
{
    componentManager_ = std::make_unique<ComponentManager>();
    entityManager_ = std::make_unique<EntityManager>();
    systemManager_ = std::make_unique<SystemManager>();
}

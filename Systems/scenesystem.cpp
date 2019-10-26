#include "scenesystem.h"
#include "World.h"
#include "types.h"
#include <QJsonArray>

void SceneSystem::clearScene()
{
    for(auto Entity : mEntities)
        getWorld()->destroyEntity(Entity);
}

void SceneSystem::loadScene(QJsonObject JSON)
{
    clearScene();

    std::unordered_map<std::string, ComponentType> ComponentTypes = getWorld()->getComponentTypes();


    Entity newEntity = getWorld()->createEntity();
    QJsonArray entityArray = JSON.take("Entities").toArray();
    QJsonArray components = entityArray.first().toArray();
    entityArray.removeFirst();

    for(auto component : components)
    {
        auto Type = component.toObject().take("Type").toInt();
        std::string SType = findComponentNameByValue(ComponentTypes, Type);


    }
}

std::string SceneSystem::findComponentNameByValue(std::unordered_map<std::string, ComponentType>& ComponentTypes, ComponentType TypeToFind)
{
    for(auto& type : ComponentTypes)
    {
        if(type.second == TypeToFind)
            return type.first;
    }
}

SceneSystem::SceneSystem()
{

}

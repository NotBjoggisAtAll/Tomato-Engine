#include "entitymanager.h"
#include "Components/allcomponents.h"
#include "resourcemanager.h"

EntityManager* EntityManager::mInstance = nullptr;
EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{
    delete mInstance;
}

EntityManager *EntityManager::instance()
{
    if(!mInstance)
        mInstance = new EntityManager();

    return mInstance;
}

unsigned int EntityManager::CreateEntity(std::string Name)
{
    mEntities[EntityID] = Name;
    return EntityID++;
}
MaterialComponent* EntityManager::addComponent(unsigned int EntityID, ComponentType Type, Shader* Shader)
{
    MaterialComponent* ComponentToReturn{nullptr};
    if(Type == ComponentType::Material)
        ComponentToReturn = ResourceManager::instance()->createMaterialComponent(EntityID, Shader);

    return ComponentToReturn;
}


Component* EntityManager::addComponent(unsigned int EntityID, ComponentType Type, std::string filePath)
{
    Component* ComponentToReturn{nullptr};

    switch (Type) {
    case ComponentType::Mesh:
        ComponentToReturn = ResourceManager::instance()->createMeshComponent(EntityID, filePath);
        break;
    case ComponentType::Light:

        break;
    case ComponentType::Sound:

        break;
    case ComponentType::Camera:

        break;
    case ComponentType::Render:

        break;

    case ComponentType::Script:

        break;
    case ComponentType::Physics:

        break;

    case ComponentType::Collision:

        break;
    case ComponentType::Transform:
        ComponentToReturn = ResourceManager::instance()->createTransformComponent(EntityID);
        break;
    default:
        break;
    }

    return ComponentToReturn;
}

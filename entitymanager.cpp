#include "entitymanager.h"
#include "Components/allcomponents.h"
#include "resourcefactory.h"

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

unsigned int EntityManager::CreateEntity()
{
    return EntityID++;
}
void EntityManager::addComponent(unsigned int EntityID, ComponentType Type, Shader* Shader)
{
    if(Type == ComponentType::Material)
        ResourceFactory::instance()->createMaterialComponent(EntityID, Shader);
}


void EntityManager::addComponent(unsigned int EntityID, ComponentType Type, std::string filePath)
{
    switch (Type) {
    case ComponentType::Mesh:
        ResourceFactory::instance()->createMeshComponent(EntityID, filePath);
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
        ResourceFactory::instance()->createTransformComponent(EntityID);
        break;
    default:
        break;
    }
}

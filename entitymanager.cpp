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

Entity EntityManager::CreateEntity(std::string Name)
{
    if(Name == "axis" || Name == "skybox")
    {
        return entity++;
    }
    mEntities[entity] = Name;

    return entity++;
}
MaterialComponent* EntityManager::addComponent(unsigned int EntityID, ComponentType Type, Shader* Shader)
{
    MaterialComponent* ComponentToReturn{nullptr};
    if(Type == ComponentType::Material)
        ComponentToReturn = ResourceManager::instance()->createMaterialComponent(EntityID, Shader);

    return ComponentToReturn;
}

Component* EntityManager::addComponent(unsigned int EntityID, ComponentType Type, std::string filePath, bool loop, float gain)
{
    Component* ComponentToReturn{nullptr};

    switch (Type) {
    case ComponentType::Mesh:
        ComponentToReturn = ResourceManager::instance()->createMeshComponent(EntityID, filePath);
        break;
    case ComponentType::Light:

        break;
    case ComponentType::Sound:
        ComponentToReturn = ResourceManager::instance()->createSoundComponent(EntityID, filePath, loop, gain);
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

void EntityManager::addChild(Entity Parent, Entity Child)
{
    auto p = ResourceManager::instance()->getTransformComponent(Parent);
    auto c = ResourceManager::instance()->getTransformComponent(Child);
    c->mParent = p;
    p->mChildren.push_back(ResourceManager::instance()->getTransformComponent(Child));
}

void EntityManager::removeRelationship(Entity Parent)
{
    auto transform = ResourceManager::instance()->getTransformComponent(Parent);
    for(auto& Child : transform->mChildren)
        Child->mParent = nullptr;

    transform->mChildren.clear();
}


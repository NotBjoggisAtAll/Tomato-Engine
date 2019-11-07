#ifndef WORLD_H
#define WORLD_H

#include "Managers/componentManager.h"
#include "Managers/entitymanager.h"
#include "Managers/systemManager.h"
#include <memory>
#include <string>

class Camera;

class World
{
public:

     friend World* getWorld()
    {
        if(instance == nullptr)
            instance = new World();

        return instance;
    }

    void init()
    {
        // Create pointers to each manager
        mComponentManager = std::make_unique<ComponentManager>();
        mEntityManager = std::make_unique<EntityManager>();
        mSystemManager = std::make_unique<SystemManager>();
    }

    // Entity methods
    Entity createEntity()
    {
        auto eId = mEntityManager->createEntity();
        return eId;
    }

    void destroyEntity(Entity entity)
    {

        mEntityManager->destroyEntity(entity);

        mComponentManager->entityDestroyed(entity);

        mSystemManager->entityDestroyed(entity);
    }

    std::vector<Entity> getEntities()
    {
       return mEntityManager->getEntities();
    }

    // Component methods
    template<typename T>
    void registerComponent()
    {
        mComponentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
        mComponentManager->addComponent<T>(entity, component);

        auto signature = mEntityManager->getSignature(entity);
        signature.set(mComponentManager->getComponentType<T>(), true);
        mEntityManager->setSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
        mComponentManager->removeComponent<T>(entity);

        auto signature = mEntityManager->getSignature(entity);
        signature.set(mComponentManager->getComponentType<T>(), false);
        mEntityManager->setSignature(entity, signature);

        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    std::optional<T*> getComponent(Entity entity)
    {
        return mComponentManager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType()
    {
        return mComponentManager->getComponentType<T>();
    }

    std::unordered_map<std::string, ComponentType> getComponentTypes()
    {
        return mComponentManager->getComponentTypes();
    }

    // System methods
    template<typename T>
    std::shared_ptr<T> registerSystem()
    {
        return mSystemManager->registerSystem<T>();
    }

    template<typename T>
    std::shared_ptr<T> getSystem()
    {
        return mSystemManager->getSystem<T>();
    }

    template<typename T>
    void setSystemSignature(Signature signature)
    {
        mSystemManager->setSignature<T>(signature);
    }

    bool bGameRunning = false;

    Camera* getCurrentCamera();
    void setCurrentCamera(Camera* newCamera);

private:

    static World* instance;
    World(){init();}

    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<SystemManager> mSystemManager;

    Camera* currentCamera_ = nullptr;
};

World* getWorld();
#endif // WORLD_H

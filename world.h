#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include "Managers/componentManager.h"
#include "Managers/entitymanager.h"
#include "Managers/systemManager.h"
#include <memory>
#include <queue>
#include <string>

class World : public QObject
{
    Q_OBJECT
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
        componentManager_ = std::make_unique<ComponentManager>();
        entityManager_ = std::make_unique<EntityManager>();
        systemManager_ = std::make_unique<SystemManager>();
    }

    // Entity methods
    Entity createEntity()
    {
        auto eId = entityManager_->createEntity();
        return eId;
    }


    void destroyEntityLater(Entity entity)
    {
        entitiesToDelete_.push(entity);
    }

    void destroyEntities()
    {
        while(!entitiesToDelete_.empty())
        {
        entityManager_->destroyEntity(entitiesToDelete_.front());
        componentManager_->entityDestroyed(entitiesToDelete_.front());
        systemManager_->entityDestroyed(entitiesToDelete_.front());
        entitiesToDelete_.pop();
        }
    }
    std::vector<Entity> getEntities()
    {
       return entityManager_->getEntities();
    }

    // Component methods
    template<typename T>
    void registerComponent()
    {
        componentManager_->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
        componentManager_->addComponent<T>(entity, component);

        auto signature = entityManager_->getSignature(entity);
        signature.set(componentManager_->getComponentType<T>(), true);
        entityManager_->setSignature(entity, signature);

        systemManager_->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
        componentManager_->removeComponent<T>(entity);

        auto signature = entityManager_->getSignature(entity);
        signature.set(componentManager_->getComponentType<T>(), false);
        entityManager_->setSignature(entity, signature);

        systemManager_->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    std::optional<T*> getComponent(Entity entity)
    {
        return componentManager_->getComponent<T>(entity);
    }

    template<typename T>
    ComponentType getComponentType()
    {
        return componentManager_->getComponentType<T>();
    }

    std::unordered_map<std::string, ComponentType> getComponentTypes()
    {
        return componentManager_->getComponentTypes();
    }

    // System methods
    template<typename T>
    std::shared_ptr<T> registerSystem()
    {
        return systemManager_->registerSystem<T>();
    }

    template<typename T>
    std::shared_ptr<T> getSystem()
    {
        return systemManager_->getSystem<T>();
    }

    template<typename T>
    void setSystemSignature(Signature signature)
    {
        systemManager_->setSignature<T>(signature);
    }

    bool bGameRunning = false;

    Entity getCurrentCamera();
    void setCurrentCamera(Entity newCamera);

signals:
    void updateCameraPerspectives();
private:


    static World* instance;
    World();

    std::unique_ptr<ComponentManager> componentManager_;
    std::unique_ptr<EntityManager> entityManager_;
    std::unique_ptr<SystemManager> systemManager_;

    std::queue<Entity> entitiesToDelete_;

    Entity currentCamera_ = -1;

};

World* getWorld();
#endif // WORLD_H

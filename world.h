#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include "Managers/componentManager.h"
#include "Managers/entitymanager.h"
#include "Managers/systemManager.h"
#include <memory>
#include <queue>
#include <string>

/**
 * The World class is the only way for a user to interact with the ECS system.
 */
class World : public QObject
{
    Q_OBJECT
public:

    /**
      * A getter for the World.
      * Singleton class.
      * @return
      */
    friend World* getWorld()
    {
        if(instance == nullptr)
            instance = new World();

        return instance;
    }

    /**
     * Used to create a Entity.
     * Calls the EntityManager to create the entity.
     * @return the Entity created.
     */
    Entity createEntity();

    /**
     * Called by the user when he wants to delete a Entity.
     * The entity is destroyed at the end of the frame.
     * @param entity - Entity.
     */
    void destroyEntityLater(Entity entity);

    /**
     * Called at the end of the frame.
     * Deletes all entities that has been queued to be deleted.
     */
    void destroyEntities();

    /**
     * A Getter to get all entitites.
     * @return a vector of entities.
     */
    std::vector<Entity> getEntities();

    template<typename T>
    /**
     * The function is used to register a component T.
     * Calls the ComponentManager registerComponent function.
     */
    void registerComponent()
    {
        componentManager_->registerComponent<T>();
    }

    template<typename T>
    /**
     * Used to a add component to the entity.
     * The ComponentManager creates the component.
     * It updates the entity signature and sends it to the systems.
     * @param entity - Entity.
     * @param component - Component T. (Must be registered before use)
     */
    void addComponent(Entity entity, T component)
    {
        componentManager_->addComponent<T>(entity, component);

        auto signature = entityManager_->getSignature(entity);
        signature.set(componentManager_->getComponentType<T>(), true);
        entityManager_->setSignature(entity, signature);

        systemManager_->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    /**
     * Used to remove a component from an entity.
     * The ComponentManager removes the component.
     * It updates the entity signature and sends it to the systems.
     * @param entity - Entity.
     */
    void removeComponent(Entity entity)
    {
        componentManager_->removeComponent<T>(entity);

        auto signature = entityManager_->getSignature(entity);
        signature.set(componentManager_->getComponentType<T>(), false);
        entityManager_->setSignature(entity, signature);

        systemManager_->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    /**
     * A getter for getting a component.
     * @param entity - Entity.
     * @return A pointer to the component wrapped in a std::optional.
     */
    std::optional<T*> getComponent(Entity entity)
    {
        return componentManager_->getComponent<T>(entity);
    }

    template<typename T>
    /**
     * Used to get the component type of a given component.
     * Used to set system signatures.
     * @return the ComponentType.
     */
    ComponentType getComponentType()
    {
        return componentManager_->getComponentType<T>();
    }

    /**
     * Used to get all component types.
     * Used to set system signatures.
     * @return a map with all ComponentTypes
     */
    std::unordered_map<std::string, ComponentType> getComponentTypes();

    template<typename T>
    /**
     * Registers a system.
     * @return a shared pointer to the system.
     */
    std::shared_ptr<T> registerSystem()
    {
        return systemManager_->registerSystem<T>();
    }

    template<typename T>
    /**
     * Gets a system of type T. (Must be registred before use)
     * @return a shared pointer to the system.
     */
    std::shared_ptr<T> getSystem()
    {
        return systemManager_->getSystem<T>();
    }

    template<typename T>
    /**
     * Used to update the system's signature.
     * @param signature
     */
    void setSystemSignature(Signature signature)
    {
        systemManager_->setSignature<T>(signature);
    }

    /// Used to check if the game is running or not.
    bool bGameRunning = false;

    /**
     * Getter for the current camera entity.
     * @return the entity of the current camera.
     */
    Entity getCurrentCamera();

    /**
     * Setter for the current camera entity.
     * @param newCamera - The new camera entity.
     */
    void setCurrentCamera(Entity newCamera);

signals:
    /**
     * Emitted when the world needs to update the camera perspectives.
     * Used when setting a new camera.
     */
    void updateCameraPerspectives();

    /**
     * Emitted when the world deletes a entity.
     * Removes the entity from the world outliner.
     */
    void updateWorldOutliner();
private:

    /// The pointer to the world singleton class.
    static World* instance;

    /**
     * Default constructor.
     * Private because its a singleton class.
     * Creates the ECS system.
     */
    World();

    /// A unique pointer to the ComponentManager.
    std::unique_ptr<ComponentManager> componentManager_;

    /// A unique pointer to the EntityManager.
    std::unique_ptr<EntityManager> entityManager_;

    /// A unique pointer to the SystemManager.
    std::unique_ptr<SystemManager> systemManager_;

    /// A queue of entities that is deleted at the end of the frame.
    std::queue<Entity> entitiesToDelete_;

    /// The entity id of the current camera.
    Entity currentCamera_ = -1;
};

World* getWorld();
#endif // WORLD_H

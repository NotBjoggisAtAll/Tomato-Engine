#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "types.h"
#include "Components/componentArray.h"
#include <string>
#include <memory>

/**
 * The ComponentManager is responsible for registering/storing/adding/removing components in the ECS system.
 * All components is stored in this Manager.
 */
class ComponentManager
{
public:

    template<typename T>
    /**
     * When registering a component, the ComponentManager creates a ID and an Array for the current Component.
     * You will need to register a component before you can use it. Otherwise the component has no place to be stored.
     * Each component can only be registered once.
     */
    void registerComponent()
    {
        std::string typeName = typeid(T).name();

        assert(componentTypes_.find(typeName) == componentTypes_.end() && "Registering component type more than once.");

        componentTypes_.insert(std::make_pair(typeName, nextComponentType_));

        ///Create a pointer to the ComponentArray<T>
        componentArrays_.insert(std::make_pair(typeName, std::make_shared<ComponentArray<T>>()));

        ++nextComponentType_;
    }

    template<typename T>
    /**
     * A getter for ComponentTypes. The Component must be registered before the type can be received.
     * @return the ComponentType (unsigned int).
     */
    ComponentType getComponentType()
    {
        std::string typeName = typeid(T).name();

        assert(componentTypes_.find(typeName) != componentTypes_.end() && "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return componentTypes_[typeName];
    }

    template<typename T>
    /**
     * Adds a component to the current Entity.
     * Calls the insertData function in the ComponentArray T.
     * @param entity - Entity. The owning Entity that you want to add a component to.
     * @param component - Component. The component you want to add to the Entity.
     */
    void addComponent(Entity entity, T component)
    {
        getComponentArray<T>()->insertData(entity, component);
    }

    template<typename T>
    /**
     * Removes a component from the current Entity.
     * Calls the removeData function in the ComponentArray T.
     * @param entity - Entity. The owning Entity that you want to remove a component from.
     */
    void removeComponent(Entity entity)
    {
        getComponentArray<T>()->removeData(entity);
    }

    template<typename T>
    /**
     * Gets a component of the current Entity.
     * Calls the getData function in the ComponentArray T.
     * @param entity - Entity. The owning Entity that you want to get the component to.
     * @return - std::optional < T* >. A std::optional with the component. Use .value() to get the actual component.
     */
    std::optional<T*> getComponent(Entity entity)
    {
        return getComponentArray<T>()->getData(entity);
    }

    /**
     * Gets called when an Entity is destroyed.
     * Goes through all ComponentArrays and removes the component of the given Entity.
     * @param entity - Entity. The Entity you want to destroy.
     */
    void entityDestroyed(Entity entity)
    {
        for (auto& pair : componentArrays_)
        {
            auto& component = pair.second;
            component->entityDestroyed(entity);
        }
    }

    /**
     * A getter for the ComponentTypes.
     * @return a copy of the map containing the ComponentTypes.
     */
    std::unordered_map<std::string, ComponentType> getComponentTypes()
    {
        return componentTypes_;
    }

private:

    /// A map where the key is the component name and the value is its ID. (ComponentType)
    std::unordered_map<std::string, ComponentType> componentTypes_{};

    /// A map where the key is the component name and the value is the ComponentArray.
    std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays_{};

    /// The component type to be assigned to the next registered component. Starting at 0.
    ComponentType nextComponentType_{};

    template<typename T>
    /**
     * Convenience function to get the statically casted pointer to the ComponentArray T.
     * @return a shared pointer to the ComponentArray T.
     */
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        std::string typeName = typeid(T).name();

        assert(componentTypes_.find(typeName) != componentTypes_.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[typeName]);
    }
};

#endif // COMPONENTMANAGER_H

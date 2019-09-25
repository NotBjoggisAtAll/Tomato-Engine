#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "types.h"
#include "Components/componentArray.h"
#include <string>
#include <memory>
class ComponentManager
{
public:

    template<typename T>
    void registerComponent()
    {
        std::string typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");


        mComponentTypes.insert(std::make_pair(typeName, mNextComponentType));

        ///Create a pointer to the ComponentArray<T>
        mComponentArrays.insert(std::make_pair(typeName, std::make_shared<ComponentArray<T>>()));

        ++mNextComponentType;
    }

    template<typename T>
    ComponentType getComponentType()
    {
        std::string typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return mComponentTypes[typeName];
    }

    template<typename T>
    void addComponent(Entity entity, T component)
    {
        getComponentArray<T>()->insertData(entity, component);
    }

    template<typename T>
    void removeComponent(Entity entity)
    {
        getComponentArray<T>()->removeData(entity);
    }

    template<typename T>
    std::optional<T*> getComponent(Entity entity)
    {
        return getComponentArray<T>()->getData(entity);
    }

    void entityDestroyed(Entity entity)
    {
        for (auto& pair : mComponentArrays)
        {
            auto& component = pair.second;
            component->entityDestroyed(entity);
        }
    }

private:


    // Map from type string pointer to a component type (aka Component ID)
    std::unordered_map<std::string, ComponentType> mComponentTypes{};

    // Map from type string pointer to a component array
    std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays{};

    // The component type to be assigned to the next registered component - starting at 0
    ComponentType mNextComponentType{};

    // Convenience function to get the statically casted pointer to the ComponentArray of type T.
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        std::string typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
    }
};

#endif // COMPONENTMANAGER_H

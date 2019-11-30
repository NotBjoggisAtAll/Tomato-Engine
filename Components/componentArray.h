#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "types.h"
#include <optional>
#include <array>
#include <unordered_map>
#include <QDebug>
#include <cassert>

struct IComponentArray
{
    virtual ~IComponentArray() = default;
    IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

/**
 * The class contains an array of a T Component (Eg. Transform).
 * It stores all the components in an array and stores the owning Entity (key) of an Component to the std::unordered_map<Entity, size_t> with arrayindex of the component as the value.
 * It also has a std::unordered_map<size_t, Entity> the other way around, so you can find the owning Entity of an Component with the help of its index in the array.
 * Also has a size variable to store the current arraysize.
 */
template <typename T>
class ComponentArray : public IComponentArray
{
public:

    /**
     * Default constructor.
     */
    ComponentArray() = default;

    /**
     * Inserts the Component T into the array.
     * Also inserts the Component index and the Entity into the unordered maps and updates the array size variable.
     * The function run an assert if the Component is already added.
     * @param entity - Entity. The owning Entity of the Component T.
     * @param component - Component T.
     */
    void insertData(Entity entity, T component)
    {
        assert(entityToIndexMap_.find(entity) == entityToIndexMap_.end() && "Component added to same entity more than once.");

        size_t newIndex = size_;

        entityToIndexMap_[entity] = newIndex;

        indexToEntityMap_[newIndex] = entity;

        componentArray_.at(newIndex) = component;

        ++size_;
    }

    /**
     * Removes the Component of the Entity from the array.
     * Uses the Entity to index map in order to find the Component to remove.
     * Updated the maps after removal and reduces the array size with 1.
     * When a Component is removed it takes the last Component in the array and moves it to the index of the removed Component.
     * This is to keep the array packed when accessing it in different systems (Cache friendly).
     * @param entity - Entity. The owner of the Component that will be removed.
     */
    void removeData(Entity entity)
    {
        if(entityToIndexMap_.find(entity) == entityToIndexMap_.end())
        {
            qDebug() << "Removing non-existent component!";
            return;
        }

        size_t indexOfRemovedEntity = entityToIndexMap_[entity];
        size_t indexOfLastElement = size_ - 1;
        componentArray_.at(indexOfRemovedEntity) = componentArray_.at(indexOfLastElement);

        Entity entityOfLastElement = indexToEntityMap_[indexOfLastElement];
        entityToIndexMap_[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap_[indexOfRemovedEntity] = entityOfLastElement;

        entityToIndexMap_.erase(entity);
        indexToEntityMap_.erase(indexOfLastElement);

        --size_;
    }

    /**
     * Searches through the Entity to index map to check if the Entity has a Component T.
     * @param entity - Entity. The entity to search for.
     * @return A std::optional with a pointer to the Component T. Returns std::nullopt if the Entity can't be found.
     */
    std::optional<T*> getData(Entity entity)
    {
        if(entityToIndexMap_.find(entity) == entityToIndexMap_.end())
        {
            return std::nullopt;
        }


        return &componentArray_.at(entityToIndexMap_[entity]);
    }

    /**
     * Searches through the Entity to index map to check if the Entity has a Component T.
     * If the Entity is found the Component is deleted.
     * @param entity - Entity.
     */
    void entityDestroyed(Entity entity) override
    {
        if (entityToIndexMap_.find(entity) != entityToIndexMap_.end())
            removeData(entity);
    }

private:

    /// The packed array of components T.
    std::array<T, MAX_ENTITIES> componentArray_;

    /// A map where the Entity is the key and the index in the array is the value.
    std::unordered_map<Entity, size_t> entityToIndexMap_;

    /// A map where the index in the array is the key and the Entity is the value.
    std::unordered_map<size_t, Entity> indexToEntityMap_;

    /// The total size of valid Components in the array.
    size_t size_{};
};

#endif // COMPONENTARRAY_H

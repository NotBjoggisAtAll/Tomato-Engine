#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "types.h"
#include <optional>
#include <array>
#include <unordered_map>
#include <iostream>
#include <cassert>

struct IComponentArray
{
    virtual ~IComponentArray() = default;
    IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:

    ComponentArray() = default;

    void insertData(Entity entity, T component)
    {
        assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

        size_t newIndex = mSize;

        mEntityToIndexMap[entity] = newIndex;

        mIndexToEntityMap[newIndex] = entity;

        mComponentArray.at(newIndex) = component;

        ++mSize;
    }

    void removeData(Entity entity)
    {
        if(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end())
        {
           std::cerr << "Removing non-existent component!";
           return;
        }

        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = mSize - 1;
        mComponentArray.at(indexOfRemovedEntity) = mComponentArray.at(indexOfLastElement);

        Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
        mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        mEntityToIndexMap.erase(entity);
        mIndexToEntityMap.erase(indexOfLastElement);

        --mSize;
    }

    std::optional<T*> getData(Entity entity)
    {
        if(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end())
        {
            return {};
        }


        return &mComponentArray.at(mEntityToIndexMap[entity]);
    }

    void entityDestroyed(Entity entity) override
    {
        if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
        {
            // Remove the entity's component if it existed
            removeData(entity);
        }
    }

private:

    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> mComponentArray;

    // Map from an entity ID to an array index.
    std::unordered_map<Entity, size_t> mEntityToIndexMap;

    // Map from an array index to an entity ID.
    std::unordered_map<size_t, Entity> mIndexToEntityMap;

    // Total size of valid entries in the array.
    size_t mSize{};
};

#endif // COMPONENTARRAY_H

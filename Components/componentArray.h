#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "types.h"
#include <optional>

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

    ComponentArray(){}

    void insertData(Entity entity, T component)
    {
        assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

        size_t newIndex = mSize;

        mEntityToIndexMap[entity] = newIndex;

        mIndexToEntityMap[newIndex] = entity;

        mComponentArray[newIndex] = component;

        ++mSize;
    }

    void removeData(Entity entity)
    {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = mSize - 1;
        mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

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


        return &mComponentArray[mEntityToIndexMap[entity]];
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
    std::unordered_map<Entity, size_t> mEntityToIndexMap; //Could use array instead

    // Map from an array index to an entity ID.
    std::unordered_map<size_t, Entity> mIndexToEntityMap;

    // Total size of valid entries in the array.
    size_t mSize{};
};

#endif // COMPONENTARRAY_H

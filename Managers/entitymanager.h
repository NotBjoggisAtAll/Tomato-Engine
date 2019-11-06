#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "types.h"
#include <queue>
#include <array>
#include <algorithm>
#include <cassert>

class EntityManager
{
public:

    EntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            mUnusedEntityPool.push(entity);
        }
    }

    Entity createEntity()
    {
        assert(mLivingEntites < MAX_ENTITIES && "Too many entities in existence.");

        Entity id = mUnusedEntityPool.front();
        mUnusedEntityPool.pop();
        mEntities.push_back(id);
        ++mLivingEntites;

        return id;
    }

    void destroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        mSignatures.at(static_cast<unsigned int>(entity)).reset();

        auto entityIt = std::find(mEntities.begin(),mEntities.end(), entity);
        if(entityIt != std::end(mEntities))
        {
            mEntities.erase(entityIt);

            mUnusedEntityPool.push(entity);
            --mLivingEntites;
        }
    }

    void setSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        mSignatures.at(static_cast<unsigned int>(entity)) = signature;

    }

    Signature getSignature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return mSignatures.at(static_cast<unsigned int>(entity));
    }

    std::vector<Entity> getEntities()
    {
        return mEntities;
    }

private:

    std::queue<Entity> mUnusedEntityPool{};

    uint32_t mLivingEntites{};

    std::vector<Entity> mEntities;

    ///Array of entites and components
    std::array<Signature, MAX_ENTITIES> mSignatures{};
};

#endif // ENTITYMANAGER_H

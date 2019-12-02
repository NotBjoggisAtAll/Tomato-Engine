#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "types.h"
#include <queue>
#include <array>
#include <algorithm>
#include <cassert>

/**
 * The EntityManager is responsible for creating/destroying entites in the ECS system.
 * All components is stored in this Manager.
 */
class EntityManager
{
public:

    /**
     * Default constructor.
     * When called the EntityManager creates a queue with unused entities.
     */
    EntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            unusedEntityPool_.push(entity);
        }
    }

    /**
     * Creates an Entity.
     * Pops the Entity at the front of the queue and stores it in a vector of living entities.
     * @return the newly created entity ID.
     */
    Entity createEntity()
    {
        assert(livingEntities_ < MAX_ENTITIES && "Too many entities in existence.");

        Entity id = unusedEntityPool_.front();
        unusedEntityPool_.pop();
        entities_.push_back(id);
        ++livingEntities_;

        return id;
    }

    /**
     * Destroys an Entity.
     * Removes the given entity from the vector and pushes it back to the queue.
     * The entity's signature is also reset.
     * @param entity - Entity. The entity you want to destroy.
     */
    void destroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        signatures_.at(static_cast<unsigned int>(entity)).reset();

        auto entityIt = std::find(entities_.begin(),entities_.end(), entity);
        if(entityIt != std::end(entities_))
        {
            entities_.erase(entityIt);

            unusedEntityPool_.push(entity);
            --livingEntities_;
        }
    }

    /**
     * Sets the entity's signature.
     * @param entity - Entity. The entity to set the signature to.
     * @param signature - Signature.
     */
    void setSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        signatures_.at(static_cast<unsigned int>(entity)) = signature;

    }

    /**
     * Gets the entity's signature.
     * @param entity - Entity. The entity you want to get the signature to.
     * @return the Signature.
     */
    Signature getSignature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return signatures_.at(static_cast<unsigned int>(entity));
    }

    /**
     * Gets the vector of living entities.
     * @return a vector of entities.
     */
    std::vector<Entity> getEntities()
    {
        return entities_;
    }

private:

    /// The pool of unused entities.
    std::queue<Entity> unusedEntityPool_{};

    /// The number of living entities.
    uint32_t livingEntities_{};

    /// The vector containing the living entities.
    std::vector<Entity> entities_;

    ///Array of the entities signatures.
    std::array<Signature, MAX_ENTITIES> signatures_{};
};

#endif // ENTITYMANAGER_H

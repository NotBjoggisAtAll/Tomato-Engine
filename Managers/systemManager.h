#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <cassert>
#include "types.h"
#include "Systems/system.h"

/**
 * The SystemManager is responsible for registering/storing/updating signatures for the systems in the ECS system.
 * All systems is stored in this Manager.
 */
class SystemManager
{
public:

    template<typename T>
    /**
     * When registering a system, the SystemManager creates the system and stores it in a map.
     * Each system can only be registered once.
     * @return a shared pointer to the System T.
     */
    std::shared_ptr<T> registerSystem()
    {
        std::string typeName = typeid(T).name();

        assert(systems_.find(typeName) == systems_.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        systems_.insert(std::make_pair(typeName, system));
        return system;
    }

    template<typename T>
    /**
     * Gets the system with typename T. Must already registered before this function is called.
     * @return a shared pointer to the System T.
     */
    std::shared_ptr<T> getSystem()
    {
        std::string typeName = typeid(T).name();

        assert(systems_.find(typeName) != systems_.end() && std::string("System " + typeName + " doesnt exist.").c_str());

        return std::static_pointer_cast<T>(systems_[typeName]);
    }

    template<typename T>
    /**
     * Sets the signature for the system.
     * @param signature - Signature. The signature to set.
     */
    void setSignature(Signature signature)
    {
        std::string typeName = typeid(T).name();

        assert(systems_.find(typeName) != systems_.end() && "System used before registered.");

        // Set the signature for this system
        signatures_.insert(std::make_pair(typeName, signature));
    }

    /**
     * Removes the entity from the system set of entities.
     * Is called when a entity is destroyed.
     * @param entity - Entity. The entity to remove.
     */
    void entityDestroyed(Entity entity)
    {
        // Erase a destroyed entity from all system lists
        // entities_ is a set so no check needed
        for (auto const& pair : systems_)
        {
            auto const& system = pair.second;

            system->entities_.erase(entity);
        }
    }

    /**
     * Updates the signature for a particluar entity.
     * Is called whenever a entity's signature is changed (aka. a component is added/removed).
     * Then the entity is either added or removed depending on what components the system needs.
     * Eg: RenderSystem needs a Transform, Mesh and Material. If either of those are removed the
     * RenderSystem does not longer need to have that entity in its set. Since the entity can't be rendered anyway.
     * @param entity - Entity.
     * @param entitySignature - Signature. The new signature of the Entity.
     */
    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        // Notify each system that an entity's signature changed
        for (auto const& pair : systems_)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures_[type];

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->entities_.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else
            {
                system->entities_.erase(entity);
            }
        }
    }

private:
    /// A map with signatures of systems. The class name is the key and the Signature is the value.
    std::unordered_map<std::string, Signature> signatures_{};

    /// A map with pointers to systems. The class name is the key and the System is the value.
    std::unordered_map<std::string, std::shared_ptr<System>> systems_{};
};

#endif // SYSTEMMANAGER_H

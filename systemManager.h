#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <string>
#include "types.h"
#include "system.h"

class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> registerSystem()
    {
        std::string typeName = typeid(T).name();

        assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        mSystems.insert(std::make_pair(typeName, system));
        return system;
    }

    template<typename T>
    void setSignature(Signature signature)
    {
        std::string typeName = typeid(T).name();

        assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

        // Set the signature for this system
        mSignatures.insert(std::make_pair(typeName, signature));
    }

    void entityDestroyed(Entity entity)
    {
        // Erase a destroyed entity from all system lists
        // mEntities is a set so no check needed
        for (auto const& pair : mSystems)
        {
            auto const& system = pair.second;

            system->mEntities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        // Notify each system that an entity's signature changed
        for (auto const& pair : mSystems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = mSignatures[type];

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->mEntities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else
            {
                system->mEntities.erase(entity);
            }
        }
    }

private:
    // Map from system type string pointer to a signature
    std::unordered_map<std::string, Signature> mSignatures{};

    // Map from system type string pointer to a system pointer
    std::unordered_map<std::string, std::shared_ptr<System>> mSystems{};
};

#endif // SYSTEMMANAGER_H

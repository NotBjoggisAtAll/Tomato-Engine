#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Components/component.h"
#include "Entity.h"
class Shader;
class TransformComponent;
class MaterialComponent;
class EntityManager
{
public:

    static EntityManager* instance();

    unsigned int CreateEmptyEntity(std::string Name);
    unsigned int CreateEntity(std::string Name);
    Component *addComponent(unsigned int EntityID, ComponentType Type, std::string filePath="", bool loop=false, float gain=1.f);
    MaterialComponent *addComponent(unsigned int EntityID, ComponentType Type, Shader *Shader);

    std::unordered_map<unsigned int, std::string> mEntities;

private:
    EntityManager();
    ~EntityManager();

    static EntityManager* mInstance;

    unsigned int EntityID = 0;

};

#endif // ENTITYMANAGER_H

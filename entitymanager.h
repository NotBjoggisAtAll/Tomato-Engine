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

    Entity CreateEntity(std::string Name);
    Component *addComponent(unsigned int entity, ComponentType Type, std::string filePath="", bool loop=false, float gain=1.f);
    MaterialComponent *addComponent(unsigned int entity, ComponentType Type, Shader *Shader);

    std::unordered_map<unsigned int, std::string> mEntities;

    /**
     * @brief To work both Entites needs to have a transform before you use this function
     * @param Parent
     * @param Child
     */
    void addChild(Entity Parent, Entity Child);

    void removeChildren(Entity Parent);

private:
    EntityManager();
    ~EntityManager();

    static EntityManager* mInstance;

    Entity entity = 0;



};

#endif // ENTITYMANAGER_H

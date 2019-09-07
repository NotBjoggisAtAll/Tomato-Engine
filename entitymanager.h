#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Components/component.h"

class Shader;

class EntityManager
{
public:

    static EntityManager* instance();

    unsigned int CreateEntity();
    void addComponent(unsigned int EntityID, ComponentType Type, std::string filePath="");
    void addComponent(unsigned int EntityID, ComponentType Type, Shader *Shader);
private:
    EntityManager();
    ~EntityManager();



    static EntityManager* mInstance;

    unsigned int EntityID = 0;
};

#endif // ENTITYMANAGER_H

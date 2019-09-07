#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


class EntityManager
{
public:
    EntityManager();

    unsigned int CreateEntity();

private:

    unsigned int EntityID = 0;
};

#endif // ENTITYMANAGER_H

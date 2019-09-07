#include "entitymanager.h"

EntityManager::EntityManager()
{

}

unsigned int EntityManager::CreateEntity()
{
    return EntityID++;
}

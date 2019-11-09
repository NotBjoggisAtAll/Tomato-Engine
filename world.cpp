#include "world.h"

World* World::instance = nullptr;

Entity World::getCurrentCamera()
{
    return currentCamera_;
}

void World::setCurrentCamera(Entity newCamera)
{
    currentCamera_ = newCamera;
}

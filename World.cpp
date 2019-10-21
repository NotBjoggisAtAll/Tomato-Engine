#include "World.h"

World* World::instance = nullptr;

Camera *World::getCurrentCamera()
{
    return currentCamera_;
}

void World::setCurrentCamera(Camera *newCamera)
{
    currentCamera_ = newCamera;
}

#include "world.h"

World* World::instance = nullptr;

CameraClass *World::getCurrentCamera()
{
    return currentCamera_;
}

void World::setCurrentCamera(CameraClass *newCamera)
{
    currentCamera_ = newCamera;
}

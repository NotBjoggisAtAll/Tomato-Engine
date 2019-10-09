#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "system.h"

#include "GSL/vector3d.h"

class CollisionSystem : public System
{
public:
    CollisionSystem();

    void checkCollision();
    void checkMouseCollision(gsl::Vector3D mousePosition);
};

#endif // COLLISIONSYSTEM_H

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "system.h"

class CollisionSystem : public System
{
public:
    CollisionSystem();

    void checkCollision();
};

#endif // COLLISIONSYSTEM_H

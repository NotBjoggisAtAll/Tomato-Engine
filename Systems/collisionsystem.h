#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "system.h"

#include "GSL/vector3d.h"

class Collision;
class Transform;

class CollisionSystem : public System
{
public:
    CollisionSystem() = default;

    void checkCollision();
    Entity checkMouseCollision(gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection);


private:
    bool intersect(Collision *collision, Transform *transform, gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, float &distance);

};

#endif // COLLISIONSYSTEM_H

#ifndef COLLISION_H
#define COLLISION_H

#include "GSL/vector3d.h"

enum class CollisionType
{
    NONE = 0,
    AABB,
    OBB,
    CIRCLE
};

struct Collision
{
    Collision(){}
    Collision(CollisionType type, gsl::Vector3D center, gsl::Vector3D corner) : type_(type), center_(center), corner_(corner) {}

    CollisionType type_ = CollisionType::NONE;
    gsl::Vector3D center_ = gsl::Vector3D(0);
    gsl::Vector3D corner_ = gsl::Vector3D(0);
};

#endif // COLLISION_H

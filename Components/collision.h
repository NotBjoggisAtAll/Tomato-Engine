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
    Collision(CollisionType type, gsl::Vector3D minVector, gsl::Vector3D maxVector) : type_(type), minVector_(minVector), maxVector_(maxVector) {}

    CollisionType type_ = CollisionType::NONE;
    gsl::Vector3D minVector_ = gsl::Vector3D(0);
    gsl::Vector3D maxVector_ = gsl::Vector3D(0);
};

#endif // COLLISION_H

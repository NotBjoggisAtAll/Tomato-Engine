#ifndef COLLISION_H
#define COLLISION_H

#include "GSL/vector3d.h"
#include <QJsonDocument>

enum class CollisionType
{
    NONE = 0,
    AABB,
    OBB,
    CIRCLE
};

struct Collision
{
    Collision() = default;
    Collision(CollisionType type, gsl::Vector3D minVector, gsl::Vector3D maxVector) : type_(type), minVector_(minVector), maxVector_(maxVector), scaledMinVector_(minVector), scaledMaxVector_(maxVector) {}

    CollisionType type_ = CollisionType::NONE;
    gsl::Vector3D minVector_ = gsl::Vector3D(0);
    gsl::Vector3D maxVector_ = gsl::Vector3D(0);

    gsl::Vector3D scaledMinVector_ = gsl::Vector3D(0);
    gsl::Vector3D scaledMaxVector_ = gsl::Vector3D(0);


};

#endif // COLLISION_H

#ifndef COLLISION_H
#define COLLISION_H

#include "GSL/vector3d.h"

class QJsonObject;
struct Collision
{
    Collision() = default;
    Collision(QJsonObject JSON);
    Collision(gsl::Vector3D minVector, gsl::Vector3D maxVector) : minVector_(minVector), maxVector_(maxVector), scaledMinVector_(minVector), scaledMaxVector_(maxVector) {}

    gsl::Vector3D minVector_ = gsl::Vector3D(0);
    gsl::Vector3D maxVector_ = gsl::Vector3D(0);

    gsl::Vector3D scaledMinVector_ = gsl::Vector3D(0);
    gsl::Vector3D scaledMaxVector_ = gsl::Vector3D(0);

    std::string filepath_ = "";


    QJsonObject toJSON();
};

#endif // COLLISION_H

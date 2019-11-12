#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GSL/vector3d.h"

struct Projectile
{
    Projectile();

    gsl::Vector3D direction_ = gsl::Vector3D(0);
    float speed_ = .1f;
    bool routeCalculated = false;

};

#endif // PROJECTILE_H

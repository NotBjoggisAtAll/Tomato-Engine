#ifndef HITRESULT_H
#define HITRESULT_H

#include "GSL/vector3d.h"
#include "GSL/vector2d.h"
#include "types.h"

struct HitResult
{
    Entity entityHit = -1;
    float distance = 0;
    gsl::Vector3D position = gsl::Vector3D(0);
};


struct HitResult2D
{
    Entity entityHit = -1;
    gsl::Vector2D entityPosition = gsl::Vector2D(0);
};

#endif // HITRESULT_H

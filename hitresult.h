#ifndef HITRESULT_H
#define HITRESULT_H

#include "GSL/vector3d.h"

struct HitResult
{
    float distance = 0;
    gsl::Vector3D position = gsl::Vector3D(0);
};

#endif // HITRESULT_H

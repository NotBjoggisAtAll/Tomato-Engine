#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GSL/vector3d.h"

struct Transform
{
    gsl::Vector3D Position{0,0,0};
    gsl::Vector3D Rotation{0,0,0};
    gsl::Vector3D Scale{1,1,1};
};

#endif // TRANSFORMCOMPONENT_H

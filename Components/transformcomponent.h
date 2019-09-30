#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GSL/vector3d.h"

struct Transform
{
    Transform(){}
    Transform(gsl::Vector3D position_, gsl::Vector3D rotation_, gsl::Vector3D scale_) : position(position_), rotation(rotation_), scale(scale_) {}
    Transform(gsl::Vector3D position_) : position(position_) {}

    gsl::Vector3D position{0,0,0};
    gsl::Vector3D rotation{0,0,0};
    gsl::Vector3D scale{1,1,1};
};

#endif // TRANSFORMCOMPONENT_H

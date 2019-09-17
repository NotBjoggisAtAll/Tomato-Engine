#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "component.h"

struct TransformComponent : public Component
{
    int  Parent{-1};
    int Child{-1};

    gsl::Matrix4x4 mMatrix;
};

#endif // TRANSFORMCOMPONENT_H

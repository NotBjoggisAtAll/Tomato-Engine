#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "component.h"

struct TransformComponent : public Component
{
    gsl::Matrix4x4 mMatrix;
};

#endif // TRANSFORMCOMPONENT_H

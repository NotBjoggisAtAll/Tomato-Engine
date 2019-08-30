#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "basecomponent.h"

struct TransformComponent : public BaseComponent
{
    gsl::Matrix4x4 mMatrix;
};

#endif // TRANSFORMCOMPONENT_H

#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "basecomponent.h"

struct MaterialComponent : public BaseComponent
{
    Shader* mShader{nullptr};
    gsl::Vector3D mColor{1,1,1};
    GLuint mTextureUnit{0};
};

#endif // MATERIALCOMPONENT_H

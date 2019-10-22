#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

class Shader;

#include "GSL/vector3d.h"

struct Material
{
    Material() = default;
    Material(Shader* Shader) : mShader(Shader), mColor(1,1,1) , mTextureUnit(0){}
    Material(Shader* Shader, GLuint TextureUnit) : mShader(Shader), mColor(1,1,1), mTextureUnit(TextureUnit){}
    Material(Shader* Shader, gsl::Vector3D Color) : mShader(Shader), mColor(Color), mTextureUnit(0){}
    Material(Shader* Shader, gsl::Vector3D Color,  GLuint TextureUnit) : mShader(Shader), mColor(Color), mTextureUnit(TextureUnit){}
    Shader* mShader{nullptr};
    gsl::Vector3D mColor{1,1,1};
    GLuint mTextureUnit{0};
};

#endif // MATERIALCOMPONENT_H

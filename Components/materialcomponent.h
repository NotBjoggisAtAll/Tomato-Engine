#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

class Shader;

#include "JBA/vector3d.h"

struct Material
{
    Material(){}
    Material(Shader* Shader) : mShader(Shader), mColor(1,1,1) , mTextureUnit(0){}
    Material(Shader* Shader, GLuint TextureUnit) : mShader(Shader), mColor(1,1,1), mTextureUnit(TextureUnit){}
    Material(Shader* Shader, jba::Vector3D Color) : mShader(Shader), mColor(Color), mTextureUnit(0){}
    Material(Shader* Shader, jba::Vector3D Color,  GLuint TextureUnit) : mShader(Shader), mColor(Color), mTextureUnit(TextureUnit){}
    Shader* mShader{nullptr};
    jba::Vector3D mColor{1,1,1};
    GLuint mTextureUnit{0};
};

#endif // MATERIALCOMPONENT_H

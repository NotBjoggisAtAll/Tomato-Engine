#include "guishader.h"
#include "world.h"
#include "Components/gui.h"
#include "Components/camera.h"
#include "Components/material.h"

GUIShader::GUIShader(const std::string shaderName, const GLchar *geometryPath) :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program_, "mMatrix" );
    objectColorUniform_ = glGetUniformLocation( program_, "objectColor");
    textureUniform_ = glGetUniformLocation(program_, "textureSampler");
}

void GUIShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    glUniformMatrix4fv(mMatrixUniform_, 1, GL_TRUE, modelMatrix->constData());
    glUniform1i(textureUniform_, static_cast<int>(material->textureUnit_));
    glUniform3f(objectColorUniform_, material->color_.x, material->color_.y, material->color_.z);
}

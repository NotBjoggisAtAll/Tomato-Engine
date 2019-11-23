#include "guishader.h"
#include "Components/gui.h"
#include "world.h"
#include "Components/camera.h"
#include "Components/material.h"

GUIShader::GUIShader(const std::string shaderName, const GLchar *geometryPath) :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program, "mMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program, "pMatrix" );
    objectColorUniform_ = glGetUniformLocation( program, "objectColor");
    textureUniform_ = glGetUniformLocation(program, "textureSampler");
}

GUIShader::~GUIShader()
{
    qDebug() << "Deleting GUIShader";
}

void GUIShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    glUniformMatrix4fv(mMatrixUniform_, 1, GL_TRUE, modelMatrix->constData());
    glUniform1i(textureUniform_, material->textureUnit_-1);
    glUniform3f(objectColorUniform_, material->color_.x, material->color_.y, material->color_.z);
}

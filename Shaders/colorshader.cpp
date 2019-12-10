#include "colorshader.h"
#include "Components/material.h"

ColorShader::ColorShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program_, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program_, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program_, "pMatrix" );
    objectColorUniform_ = glGetUniformLocation( program_, "objectColor" );
}

void ColorShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    Shader::transmitUniformData(modelMatrix);

    glUniform3f(objectColorUniform_, material->color_.x, material->color_.y, material->color_.z);
}

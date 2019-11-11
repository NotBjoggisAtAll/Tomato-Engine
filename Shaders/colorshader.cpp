#include "colorshader.h"
#include "Components/material.h"

ColorShader::ColorShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program, "pMatrix" );
    objectColorUniform_ = glGetUniformLocation( program, "objectColor" );
}


void ColorShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    Shader::transmitUniformData(modelMatrix);

    glUniform3f(objectColorUniform_, material->color_.x, material->color_.y, material->color_.z);
}

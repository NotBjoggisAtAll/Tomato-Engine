#include "textureshader.h"
#include "Components/material.h"

TextureShader::TextureShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program_, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program_, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program_, "pMatrix" );
    objectColorUniform_ = glGetUniformLocation( program_, "objectColor" );
    textureUniform_ = glGetUniformLocation(program_, "textureSampler");
}

void TextureShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    Shader::transmitUniformData(modelMatrix);
    glUniform1i(textureUniform_, static_cast<int>(material->textureUnit_));
    glUniform3f(objectColorUniform_, material->color_.x, material->color_.y, material->color_.z);
}

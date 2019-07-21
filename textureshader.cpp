#include "innpch.h"
#include "textureshader.h"
#include "material.h"

TextureShader::TextureShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath)
    :Shader(vertexPath, fragmentPath, geometryPath)
{
    mMatrixUniform = glGetUniformLocation( program, "mMatrix" );
    vMatrixUniform = glGetUniformLocation( program, "vMatrix" );
    pMatrixUniform = glGetUniformLocation( program, "pMatrix" );
    objectColorUniform = glGetUniformLocation( program, "objectColor" );
    textureUniform = glGetUniformLocation(program, "textureSampler");
}

void TextureShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material)
{
    Shader::transmitUniformData(modelMatrix);

    glUniform1i(textureUniform, material->mTextureUnit); //TextureUnit = 0 as default);
    glUniform3f(objectColorUniform, material->mObjectColor.x, material->mObjectColor.y, material->mObjectColor.z);
}

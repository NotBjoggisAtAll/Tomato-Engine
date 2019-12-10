#include "plainshader.h"

PlainShader::PlainShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program_, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program_, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program_, "pMatrix" );
}

void PlainShader::transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material */*material*/)
{
    Shader::transmitUniformData(modelMatrix);
}

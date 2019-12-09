#include "plainshader.h"
#include "Components/material.h"

PlainShader::PlainShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program, "pMatrix" );

}

PlainShader::~PlainShader()
{
    qDebug() << "Deleting ColorShader";
}

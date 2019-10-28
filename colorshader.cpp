#include "colorshader.h"
#include "Components/material.h"

ColorShader::ColorShader(const std::string shaderName, const GLchar *geometryPath)
    :Shader(shaderName, geometryPath)
{
    mMatrixUniform_ = glGetUniformLocation( program, "mMatrix" );
    vMatrixUniform_ = glGetUniformLocation( program, "vMatrix" );
    pMatrixUniform_ = glGetUniformLocation( program, "pMatrix" );
}

ColorShader::~ColorShader()
{
    qDebug() << "Deleting ColorShader";
}

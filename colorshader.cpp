#include "innpch.h"
#include "colorshader.h"

ColorShader::ColorShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath)
    :Shader(vertexPath, fragmentPath, geometryPath)
{
    mMatrixUniform = glGetUniformLocation( program, "mMatrix" );
    vMatrixUniform = glGetUniformLocation( program, "vMatrix" );
    pMatrixUniform = glGetUniformLocation( program, "pMatrix" );
}

ColorShader::~ColorShader()
{
    qDebug() << "Deleting ColorShader";
}

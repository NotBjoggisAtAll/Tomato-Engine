#ifndef COLORSHADER_H
#define COLORSHADER_H

#include "shader.h"

class ColorShader : public Shader
{
public:
    ColorShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath = nullptr);
};

#endif // COLORSHADER_H

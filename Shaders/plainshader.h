#ifndef PLAINSHADER_H
#define PLAINSHADER_H

#include "shader.h"

class PlainShader : public Shader
{
public:
    PlainShader(const std::string shaderName, const GLchar *geometryPath = nullptr);
    virtual ~PlainShader() override;
};


#endif // PLAINSHADER_H

#ifndef COLORSHADER_H
#define COLORSHADER_H

#include "shader.h"

class ColorShader : public Shader
{
public:
    ColorShader(const std::string shaderName, const GLchar *geometryPath=nullptr);
    void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

private:
    GLint objectColorUniform_{-1};
};

#endif // COLORSHADER_H

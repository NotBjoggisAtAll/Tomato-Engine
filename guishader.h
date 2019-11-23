#ifndef GUISHADER_H
#define GUISHADER_H

#include "shader.h"

struct GUI;

class GUIShader : public Shader
{
public:
    GUIShader(const std::string shaderName, const GLchar *geometryPath = nullptr);
    virtual ~GUIShader() override;
    virtual void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

private:

    GLint textureUniform_ = -1;
    GLint objectColorUniform_ = -1;


};

#endif // GUISHADER_H

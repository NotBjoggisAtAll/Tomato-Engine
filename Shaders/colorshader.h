#ifndef COLORSHADER_H
#define COLORSHADER_H

#include "shader.h"

/**
 * A simple shader with a RGB color.
 */
class ColorShader : public Shader
{
public:
    /**
     * Default constructor.
     * Binds uniforms. See the base Shader class for more info.
     * @param shaderName
     * @param geometryPath
     */
    ColorShader(const std::string shaderName, const GLchar *geometryPath=nullptr);

    /**
     * Sends uniform data to the shader.
     * Sends the color data to the shader.
     * @param modelMatrix - gsl::Matrix4x4. Handled by the base Shader class.
     * @param material - Material component.
     */
    void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

private:
    /// The object color uniform.
    GLint objectColorUniform_ = -1;
};

#endif // COLORSHADER_H

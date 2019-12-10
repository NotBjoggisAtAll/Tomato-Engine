#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H

#include "shader.h"

/**
 * A shader with a color and a texture.
 */
class TextureShader : public Shader
{
public:
    /**
     * Default constructor.
     * Binds uniforms. See the base Shader class for more info.
     * @param shaderName
     * @param geometryPath
     */
    TextureShader(const std::string shaderName, const GLchar *geometryPath = nullptr);

    /**
     * Sends uniform data to the shader.
     * Sends the color and texture data to the shader.
     * @param modelMatrix - gsl::Matrix4x4. Handled by the base Shader class.
     * @param material - Material component.
     */
    void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

private:
    /// The object color uniform.
    GLint objectColorUniform_ = -1;

    /// The texture ID uniform.
    GLint textureUniform_ = -1;
};

#endif // TEXTURESHADER_H

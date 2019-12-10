#ifndef GUISHADER_H
#define GUISHADER_H

#include "shader.h"

/**
 * A shader with a color and a texture. Used to render thing as 2D on the screen. (Not in the actual world).
 */
class GUIShader : public Shader
{
public:
    /**
     * Default constructor.
     * Binds uniforms. See the base Shader class for more info.
     * @param shaderName
     * @param geometryPath
     */
    GUIShader(const std::string shaderName, const GLchar *geometryPath=nullptr);

    /**
     * Sends uniform data to the shader.
     * Sends the color and texture data to the shader.
     * This also handles the model matrix. The GUIShader doesn't need the projection and view matrix because it's rendered at clip space.
     * @param modelMatrix - gsl::Matrix4x4.
     * @param material - Material component.
     */
    virtual void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

private:

    /// The texture ID uniform.
    GLint textureUniform_ = -1;

    /// The object color uniform.
    GLint objectColorUniform_ = -1;
};

#endif // GUISHADER_H

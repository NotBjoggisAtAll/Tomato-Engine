#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader.h"
#include "types.h"

struct Light;
struct Transform;

/**
 * The shader contains information about the light in the scene.
 * This is information like its position and its color.
 * The shader also contains information on how the object should
 * react to the light.
 */
class PhongShader : public Shader
{
public:
    /**
     * Default constructor.
     * Binds uniforms. See the base Shader class for more info.
     * @param shaderName
     * @param geometryPath
     */
    PhongShader(const std::string shaderName, const GLchar *geometryPath = nullptr);

    /**
     * Sends uniform data to the shader.
     * Sends the color,position and other uniforms to the shader.
     * The setLight function needs to run before this is used.
     * If not the function won't send anything to the shader.
     * @param modelMatrix - gsl::Matrix4x4. Handled by the base Shader class.
     * @param material - Material component.
     */
    void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

    /**
     * Because the phongshader needs information outside of the entity it belongs to you also need to give the shader the light Entity id.
     * @param entity - Entity.
     */
    void setLight(Entity entity);

private:
    /// The light color uniform.
    GLint lightColorUniform_ = -1;

    /// The object color uniform.
    GLint objectColorUniform_ = -1;

    /// The ambient light strength unform.
    GLint ambientLightStrengthUniform_ = -1;

    /// The light position uniform.
    GLint lightPositionUniform_ = -1;

    /// The camera position uniform.
    GLint cameraPositionUniform_ = -1;

    /// The specular strength uniform.
    GLint specularStrengthUniform_ = -1;

    /// The specular exponent uniform.
    GLint specularExponentUniform_ = -1;

    /// The light power uniform.
    GLint lightPowerUniform_ = -1;

    /// The light component.
    Light* light_ = nullptr;

    /// The light's Transform component.
    Transform* lightTransform_ = nullptr;
};

#endif // PHONGSHADER_H

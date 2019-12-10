#ifndef PLAINSHADER_H
#define PLAINSHADER_H

#include "shader.h"

/**
 * A very simple shader using the object's normal as a color. Doesn't send any uniform data.
 */
class PlainShader : public Shader
{
public:
    /**
     * Default constructor.
     * Binds uniforms. See the base Shader class for more info.
     * @param shaderName
     * @param geometryPath
     */
    PlainShader(const std::string shaderName, const GLchar *geometryPath = nullptr);

    /**
     * Sends uniform data to the shader.
     * @param modelMatrix - gsl::Matrix4x4. Handled by the base Shader class.
     * @param material - Material component.
     */
    virtual void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material = nullptr) override;
};


#endif // PLAINSHADER_H

#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_1_Core>

namespace gsl {
class Matrix4x4;
};
struct Material;

/**
 * Base class for Shaders.
 * This class loads and creates the shaders from a given files.
 * I also stores and sends the most used uniforms like the model, view and projection matrices.
 * Never directly used as a shader.
 */
class Shader : protected QOpenGLFunctions_4_1_Core
{
public:
    /**
     * Default constructor.
     * Loads and creates the shader form the given files.
     * Assumes the shaders is located under the Shaders folder.
     * @param shaderName - std::string. The shader name. The constructor adds the file extention.
     * @param geometryPath - GLchar.
     */
    Shader(const std::string shaderName, const GLchar *geometryPath = nullptr);

    /**
     * Default deconstructor.
     * Deletes the shader.
     */
    virtual ~Shader();

    /**
     * Gets the shader program.
     * @return a GLuint ID.
     */
    GLuint getProgram() const;

    /**
     * Sends uniform data to the shader.
     * The function of the base class sends the model, view and projection matrix.
     * Other uniform data needs to be specified in the Material component.
     * @param modelMatrix - gsl::Matrix4x4.
     * @param material - Material pointer.
     */
    virtual void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material = nullptr);

    /// The shader name. Used for logging and for displaying it in the editor.
    std::string shaderName_ = "";

protected:
    /// The program ID. Generated when creating the shader.
    GLuint program_ = 0;

    /// The model matrix uniform ID.
    GLint mMatrixUniform_ = -1;

    /// The view matrix uniform ID.
    GLint vMatrixUniform_ = -1;

    /// The projection matrix uniform ID.
    GLint pMatrixUniform_ = -1;
};

#endif

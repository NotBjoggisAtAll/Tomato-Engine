#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_1_Core>
#include "GSL/matrix4x4.h"

class Material;
class Camera;

class Shader : protected QOpenGLFunctions_4_1_Core
{
public:
    // Constructor generates the shader on the fly
    Shader(const std::string shaderName, const GLchar *geometryPath = nullptr );
    virtual ~Shader();

    // Use the current shader
    void use( );

    //Get program number for this shader
    GLuint getProgram() const;

    virtual void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material = nullptr);

    void setCurrentCamera(Camera *currentCamera);

    Camera *getCurrentCamera() const;

    std::string mShaderName = "";

protected:
    GLuint program{0};
    GLint mMatrixUniform_{-1};
    GLint vMatrixUniform_{-1};
    GLint pMatrixUniform_{-1};

    Camera *mCurrentCamera{nullptr};

};

#endif

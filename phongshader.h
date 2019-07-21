#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader.h"

class PhongShader : public Shader
{
public:
    PhongShader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath = nullptr);

    void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

    void setLight(class Light *light);

private:
    //    GLint textureUniform{-1};
    GLint mLightColorUniform{-1};
    GLint mObjectColorUniform{-1};
    GLint mAmbientLightStrengthUniform{-1};
    GLint mLightPositionUniform{-1};
    GLint mCameraPositionUniform{-1};
    GLint mSpecularStrengthUniform{-1};
    GLint mSpecularExponentUniform{-1};
    GLint mLightPowerUniform{-1};

    class Light *mLight;
};

#endif // PHONGSHADER_H

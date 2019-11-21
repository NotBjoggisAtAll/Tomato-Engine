#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader.h"
#include "types.h"

struct Light;
struct Transform;

class PhongShader : public Shader
{
public:
    PhongShader(const std::string shaderName, const GLchar *geometryPath = nullptr);
    virtual ~PhongShader() override;

    void transmitUniformData(gsl::Matrix4x4 *modelMatrix, Material *material) override;

    void setLight(Entity entity);

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

    Light* lightComponent = nullptr;
    Transform* lightTransformComponent = nullptr;
};

#endif // PHONGSHADER_H

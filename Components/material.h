#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "component.h"
#include "GSL/vector3d.h"
#include "Managers/shadermanager.h"

class Shader;

struct Material : public Component
{
    Material() = default;
    Material(Shader* Shader);
    Material(Shader* Shader, GLuint TextureUnit);
    Material(Shader* Shader, gsl::Vector3D Color);
    Material(Shader* Shader, gsl::Vector3D Color,  GLuint TextureUnit);
    Material(QJsonObject Json);

    Shader* shader_{nullptr};
    gsl::Vector3D color_{1,1,1};
    GLuint textureUnit_{0};

    QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // MATERIALCOMPONENT_H

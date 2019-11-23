#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "component.h"
#include "GSL/vector3d.h"

class Shader;

struct Material : public Component
{
    Material() = default;
    Material(Shader* Shader);
    Material(Shader* Shader, std::string texture);
    Material(Shader* Shader, gsl::Vector3D Color);
    Material(Shader* Shader, gsl::Vector3D Color,  std::string texture);
    Material(QJsonObject Json);

    Shader* shader_{nullptr};
    gsl::Vector3D color_{1,1,1};
    std::string textureFile_ = "";
    GLuint textureUnit_{0};

    QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // MATERIALCOMPONENT_H

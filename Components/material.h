#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "GSL/vector3d.h"
#include "Managers/shadermanager.h"

class QJsonObject;
class Shader;

struct Material
{
    Material() = default;
    Material(Shader* Shader);
    Material(Shader* Shader, GLuint TextureUnit);
    Material(Shader* Shader, gsl::Vector3D Color);
    Material(Shader* Shader, gsl::Vector3D Color,  GLuint TextureUnit);
    Material(QJsonObject JSON);

    Shader* shader_{nullptr};
    gsl::Vector3D color_{1,1,1};
    GLuint textureUnit_{0};

    QJsonObject toJson();
};

#endif // MATERIALCOMPONENT_H

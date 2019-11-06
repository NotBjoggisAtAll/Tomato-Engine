#ifndef LIGHT_H
#define LIGHT_H

#include "component.h"
#include "gltypes.h"
#include "GSL/vector3d.h"

struct Light : public Component
{

    Light() = default;
    Light(QJsonObject Json);

    GLfloat ambientStrength_{0.3f};
    gsl::Vector3D ambientColor_{0.3f, 0.3f, 0.3f};

    GLfloat lightStrength_{0.7f};
    gsl::Vector3D lightColor_{0.3f, 0.3f, 0.3f};

    GLfloat specularStrength_{0.3f};
    GLint specularExponent_{4};

    QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};
#endif // LIGHT_H

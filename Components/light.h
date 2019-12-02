#ifndef LIGHT_H
#define LIGHT_H

#include "component.h"
#include "gltypes.h"
#include "GSL/vector3d.h"

/**
 * A Component storing Light information. Used by the PhongShader.
 */
struct Light : public Component
{
    /**
     * Default constructor.
     */
    Light() = default;

    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Light component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Light(QJsonObject Json);

    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    QJsonObject toJson() override;

    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    void fromJson(QJsonObject Json) override;

    /// The ambient strength.
    GLfloat ambientStrength_{0.3f};

    /// The ambient color.
    gsl::Vector3D ambientColor_{0.3f, 0.3f, 0.3f};

    /// The light strength.
    GLfloat lightStrength_{0.7f};

    /// The light color.
    gsl::Vector3D lightColor_{0.3f, 0.3f, 0.3f};

    /// The specular strength.
    GLfloat specularStrength_{0.3f};

    /// The specular exponent.
    GLint specularExponent_{4};
};
#endif // LIGHT_H

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "component.h"
#include "GSL/vector3d.h"

/**
 * The Transform component contains information regarding the Entity's position, rotation and scale.
 */
struct Transform : public Component
{
    /**
      * Default Constructor.
      */
    Transform() = default;

    /**
     * Constructor that takes in a position.
     * @param Position - gsl::Vector3D
     */
    Transform(gsl::Vector3D Position);

    /**
     * Constructor that takes in a position and rotation.
     * @param Position - gsl::Vector3D
     * @param Rotation - gsl::Vector3D
     */
    Transform(gsl::Vector3D Position, gsl::Vector3D Rotation);

    /**
     * Constructor that takes in a position, rotation and scale.
     * @param Position - gsl::Vector3D
     * @param Rotation - gsl::Vector3D
     * @param Scale - gsl::Vector3D
     */
    Transform(gsl::Vector3D Position, gsl::Vector3D Rotation, gsl::Vector3D Scale);

    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Transform component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Transform(QJsonObject Json);

    /**
     * Makes a QJsonObject containing the Transform data.
     * @return Returns a QJsonObject
     */
    QJsonObject toJson() override;

    /**
     * Takes in a QJsonObject.
     * Override the data in the Transform with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    void fromJson(QJsonObject Json) override;
    ///Position.
    gsl::Vector3D position_ = {0,0,0};
    ///Rotation
    gsl::Vector3D rotation_ = {0,0,0};
    ///Scale
    gsl::Vector3D scale_ = {1,1,1};
};
#endif // TRANSFORMCOMPONENT_H

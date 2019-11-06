#ifndef COLLISION_H
#define COLLISION_H

#include "component.h"
#include "GSL/vector3d.h"

/**
 * The Collision component contains information regarding the object's collision.
 * Contains a min and a max gsl::Vector3D for storing the size of the collision box.
 */
struct Collision : public Component
{
    /**
      * Default Constructor.
      */
    Collision() = default;

    /**
     * Constructor that takes in a  min and max gsl::Vector3D.
     * @param minVector - gsl::Vector3D
     * @param maxVector - gsl::Vector3D
     */
    Collision(gsl::Vector3D minVector, gsl::Vector3D maxVector);

    /**
     * Constructor that takes in a QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwhise a default Collision is made.
     * @param Json - QJsonObject
     */
    Collision(QJsonObject Json);

    /**
     * Makes a QJsonObject containing the Collision data.
     * The QJsonObject only contains the filepath to the Mesh.
     * @return Returns a QJsonObject
     */
    QJsonObject toJson() override;

    /**
     * Takes in a QJsonObject
     * Overrides the data in the Collision.
     * It uses the filepath to get the data from the ResourceFactory.
     * @param Json
     */
    void fromJson(QJsonObject Json) override;

    ///Min vector
    gsl::Vector3D minVector_ = gsl::Vector3D(0);
    ///Max vector
    gsl::Vector3D maxVector_ = gsl::Vector3D(0);

    ///Min scaled vector. Made by the MovementSystem when changing the Transform's scale.
    gsl::Vector3D scaledMinVector_ = gsl::Vector3D(0);
    ///Max scaled vector. Made by the MovementSystem when changing the Transform's scale.
    gsl::Vector3D scaledMaxVector_ = gsl::Vector3D(0);

    ///Filepath for the Mesh. Used to get the collision from the ResourceFactory.
    std::string filepath_ = "";


};

#endif // COLLISION_H

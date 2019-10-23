#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "GSL/vector3d.h"
#include <QJsonObject>
#include <QJsonArray>

struct Transform
{
    Transform() = default;
    Transform(gsl::Vector3D position_, gsl::Vector3D rotation_, gsl::Vector3D scale_) : position(position_), rotation(rotation_), scale(scale_) {}
    Transform(gsl::Vector3D position_) : position(position_) {}

    gsl::Vector3D position{0,0,0};
    gsl::Vector3D rotation{0,0,0};
    gsl::Vector3D scale{1,1,1};

    Transform(QJsonObject JSON)
    {
        QJsonArray positionArray = JSON.take("Position").toArray();
        position.x = static_cast<float>(positionArray.at(0).toDouble());
        position.y = static_cast<float>(positionArray.at(1).toDouble());
        position.z = static_cast<float>(positionArray.at(2).toDouble());

        QJsonArray rotationArray = JSON.take("Rotation").toArray();
        rotation.x = static_cast<float>(rotationArray.at(0).toDouble());
        rotation.y = static_cast<float>(rotationArray.at(1).toDouble());
        rotation.z = static_cast<float>(rotationArray.at(2).toDouble());

        QJsonArray scaleArray = JSON.take("Scale").toArray();
        scale.x = static_cast<float>(scaleArray.at(0).toDouble());
        scale.y = static_cast<float>(scaleArray.at(1).toDouble());
        scale.z = static_cast<float>(scaleArray.at(2).toDouble());

    }

    QJsonObject toJSON()
    {
        QJsonObject Object;
        QJsonArray positionArray;
        positionArray.insert(0, QJsonValue(static_cast<double>(position.x)));
        positionArray.insert(1, QJsonValue(static_cast<double>(position.y)));
        positionArray.insert(2, QJsonValue(static_cast<double>(position.z)));
        Object.insert("Position", positionArray);

        QJsonArray rotationArray;
        rotationArray.insert(0, QJsonValue(static_cast<double>(rotation.x)));
        rotationArray.insert(1, QJsonValue(static_cast<double>(rotation.y)));
        rotationArray.insert(2, QJsonValue(static_cast<double>(rotation.z)));
        Object.insert("Rotation", rotationArray);

        QJsonArray scaleArray;
        scaleArray.insert(0, QJsonValue(static_cast<double>(scale.x)));
        scaleArray.insert(1, QJsonValue(static_cast<double>(scale.y)));
        scaleArray.insert(2, QJsonValue(static_cast<double>(scale.z)));
        Object.insert("Scale", scaleArray);

        return Object;
    }

};

#endif // TRANSFORMCOMPONENT_H

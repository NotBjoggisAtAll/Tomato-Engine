#include "transform.h"
#include <QJsonObject>
#include <QJsonArray>

Transform::Transform(gsl::Vector3D Position) : position_(Position) {}

Transform::Transform(gsl::Vector3D Position, gsl::Vector3D Rotation) : position_(Position), rotation_(Rotation) {}

Transform::Transform(gsl::Vector3D Position, gsl::Vector3D Rotation, gsl::Vector3D Scale) : position_(Position), rotation_(Rotation), scale_(Scale) {}


Transform::Transform(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Transform::toJson()
{
    QJsonObject object;

    QJsonArray positionArray;
    positionArray.insert(0, QJsonValue(static_cast<double>(position_.x)));
    positionArray.insert(1, QJsonValue(static_cast<double>(position_.y)));
    positionArray.insert(2, QJsonValue(static_cast<double>(position_.z)));
    object.insert("position", positionArray);

    QJsonArray rotationArray;
    rotationArray.insert(0, QJsonValue(static_cast<double>(rotation_.x)));
    rotationArray.insert(1, QJsonValue(static_cast<double>(rotation_.y)));
    rotationArray.insert(2, QJsonValue(static_cast<double>(rotation_.z)));
    object.insert("rotation", rotationArray);

    QJsonArray scaleArray;
    scaleArray.insert(0, QJsonValue(static_cast<double>(scale_.x)));
    scaleArray.insert(1, QJsonValue(static_cast<double>(scale_.y)));
    scaleArray.insert(2, QJsonValue(static_cast<double>(scale_.z)));
    object.insert("scale", scaleArray);

    return object;
}

void Transform::fromJson(QJsonObject Json)
{
    if(!Json.contains("position") || !Json.contains("rotation") || !Json.contains("scale"))
        return;

    QJsonArray positionArray = Json.take("position").toArray();
    position_.x = static_cast<float>(positionArray.at(0).toDouble());
    position_.y = static_cast<float>(positionArray.at(1).toDouble());
    position_.z = static_cast<float>(positionArray.at(2).toDouble());

    QJsonArray rotationArray = Json.take("rotation").toArray();
    rotation_.x = static_cast<float>(rotationArray.at(0).toDouble());
    rotation_.y = static_cast<float>(rotationArray.at(1).toDouble());
    rotation_.z = static_cast<float>(rotationArray.at(2).toDouble());

    QJsonArray scaleArray = Json.take("scale").toArray();
    scale_.x = static_cast<float>(scaleArray.at(0).toDouble());
    scale_.y = static_cast<float>(scaleArray.at(1).toDouble());
    scale_.z = static_cast<float>(scaleArray.at(2).toDouble());
}

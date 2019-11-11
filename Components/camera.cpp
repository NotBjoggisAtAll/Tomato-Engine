#include "camera.h"
#include <QJsonArray>

Camera::Camera()
{

}


QJsonObject Camera::toJson()
{
    QJsonObject object;

    object.insert("pitch", static_cast<double>(pitch_));
    object.insert("yaw", static_cast<double>(yaw_));

    object.insert("speed", static_cast<double>(speed_));
    object.insert("rotateSpeed", static_cast<double>(rotateSpeed_));

    object.insert("aspectRatio", static_cast<double>(aspectRatio_));
    object.insert("fieldOfView", static_cast<double>(fieldOfView_));

    return object;
}

void Camera::fromJson(QJsonObject Json)
{
    pitch_ = static_cast<float>(Json.take("pitch").toDouble());
    yaw_ = static_cast<float>(Json.take("yaw").toDouble());

    speed_ = static_cast<float>(Json.take("speed").toDouble());
    rotateSpeed_ = static_cast<float>(Json.take("rotateSpeed").toDouble());

    aspectRatio_ = static_cast<float>(Json.take("aspectRatio").toDouble());
    fieldOfView_ = static_cast<float>(Json.take("fieldOfView").toDouble());

}

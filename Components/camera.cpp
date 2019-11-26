#include "camera.h"
#include <QJsonArray>

Camera::Camera(bool isInUse) : isInUse_(isInUse){}

Camera::Camera(bool isInUse, float yaw, float pitch) : yaw_(yaw), pitch_(pitch), isInUse_(isInUse){}

Camera::Camera(float yaw, float pitch) : yaw_(yaw), pitch_(pitch) {}

Camera::Camera(QJsonObject Json)
{
    fromJson(Json);
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

    object.insert("isEditor", isEditor);

    return object;
}

void Camera::fromJson(QJsonObject Json)
{
    if(!Json.contains("pitch"))
        return;

    pitch_ = static_cast<float>(Json.take("pitch").toDouble());
    yaw_ = static_cast<float>(Json.take("yaw").toDouble());

    speed_ = static_cast<float>(Json.take("speed").toDouble());
    rotateSpeed_ = static_cast<float>(Json.take("rotateSpeed").toDouble());

    aspectRatio_ = static_cast<float>(Json.take("aspectRatio").toDouble());
    fieldOfView_ = static_cast<float>(Json.take("fieldOfView").toDouble());

    isEditor = Json.take("isEditor").toBool();

}

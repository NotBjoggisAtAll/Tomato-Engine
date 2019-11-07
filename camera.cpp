#include "camera.h"
#include <QJsonObject>
#include <QJsonArray>
#include "GSL/gsl_math.h"

Camera::Camera(gsl::Vector3D position) : position_(position){}

void Camera::pitch(float degrees)
{
    //  rotate around mRight
    pitch_ -= degrees * rotateSpeed_;
    updateForwardVector();
}

void Camera::yaw(float degrees)
{
    // rotate around mUp
    yaw_ -= degrees * rotateSpeed_;
    updateForwardVector();
}

void Camera::updateRightVector()
{
    right_ = forward_^up_;
    right_.normalize();
//    qDebug() << "Right " << mRight;
}

void Camera::updateForwardVector()
{
    right_ = gsl::Vector3D(1.f, 0.f, 0.f);
    right_.rotateY(yaw_);
    right_.normalize();
    up_ = gsl::Vector3D(0.f, 1.f, 0.f);
    up_.rotateX(pitch_);
    up_.normalize();
    forward_ = up_^right_;

    updateRightVector();
}

void Camera::calculateFrustum()
{
    auto vpMatrix = projectionMatrix_ * viewMatrix_;

    gsl::Vector3D col1(vpMatrix[0], vpMatrix[2], vpMatrix[2]);
    gsl::Vector3D col2(vpMatrix[4], vpMatrix[5], vpMatrix[6]);
    gsl::Vector3D col3(vpMatrix[8], vpMatrix[9], vpMatrix[10]);
    gsl::Vector3D col4(vpMatrix[12], vpMatrix[13], vpMatrix[14]);

    frustum_[0].normal_ = col4 + col1;
    frustum_[1].normal_ = col4 - col1;
    frustum_[2].normal_ = col4 - col2;
    frustum_[3].normal_ = col4 + col2;
    frustum_[4].normal_ = col4 - col3;
    frustum_[5].normal_ = col3;
    frustum_[0].distance_ = vpMatrix[15] + vpMatrix[3];
    frustum_[1].distance_ = vpMatrix[15] - vpMatrix[3];
    frustum_[2].distance_ = vpMatrix[15] - vpMatrix[7];
    frustum_[3].distance_ = vpMatrix[15] + vpMatrix[7];
    frustum_[4].distance_ = vpMatrix[15] - vpMatrix[11];
    frustum_[5].distance_ = vpMatrix[11];
    for (unsigned int i = 0; i < 6; ++i) {
        float magnitude = 1.0f /
        frustum_[i].normal_.length();
        frustum_[i].normal_ = frustum_[i].normal_ * magnitude;
        frustum_[i].distance_ = frustum_[i].distance_ * magnitude;
    }

}

void Camera::update()
{
    gsl::Matrix4x4 yawMatrix;
    gsl::Matrix4x4 pitchMatrix;

    pitchMatrix.rotateX(pitch_);
    yawMatrix.rotateY(yaw_);

    position_ -= forward_ * speed_;

    viewMatrix_ = pitchMatrix* yawMatrix;
    viewMatrix_.translate(-position_);
    calculateFrustum();
}

void Camera::setPosition(const gsl::Vector3D &position)
{
    position_ = position;
}

void Camera::moveForward(float speed)
{
    speed_ = speed;
}

void Camera::moveUp(float speed)
{
    position_.y += speed;
}

void Camera::moveRight(float speed)
{
    //This fixes a bug in the up and right calculations
    //so camera always holds its height when straifing
    //should be fixed thru correct right calculations!
    gsl::Vector3D right = right_;
    right.y = 0.f;
    position_ += right * speed;
}

gsl::Vector3D Camera::position() const
{
    return position_;
}

gsl::Vector3D Camera::up() const
{
    return up_;
}

gsl::Vector3D Camera::forward() const
{
    return forward_;
}

void Camera::setSpeed(float value)
{
    speed_ += value;

    //Keep within min and max values
    if(speed_ < 0.01f)
        speed_ = 0.01f;
    if (speed_ > 0.3f)
        speed_ = 0.3f;
}

float Camera::getSpeed() const
{
    return speed_;
}


Camera::Camera(QJsonObject Json)
{
    QJsonArray position = Json.take("position").toArray();
    position_.x = static_cast<float>(position.at(0).toDouble());
    position_.y = static_cast<float>(position.at(1).toDouble());
    position_.z = static_cast<float>(position.at(2).toDouble());
}

QJsonObject Camera::toJson()
{
    QJsonObject object;
    QJsonArray position;
    position.insert(0, static_cast<double>(position_.x));
    position.insert(1, static_cast<double>(position_.y));
    position.insert(2, static_cast<double>(position_.z));

    object.insert("position", position);
    return object;
}

void Camera::fromJson(QJsonObject Json)
{
    QJsonArray position = Json.take("position").toArray();
    position_.x = static_cast<float>(position.at(0).toDouble());
    position_.y = static_cast<float>(position.at(1).toDouble());
    position_.z = static_cast<float>(position.at(2).toDouble());
}

#include "camera.h"
#include <QJsonObject>
#include <QJsonArray>

Camera::Camera(gsl::Vector3D position) : mPosition(position){}

void Camera::pitch(float degrees)
{
    //  rotate around mRight
    mPitch -= degrees;
    updateForwardVector();
}

void Camera::yaw(float degrees)
{
    // rotate around mUp
    mYaw -= degrees;
    updateForwardVector();
}

void Camera::updateRightVector()
{
    mRight = mForward^mUp;
    mRight.normalize();
//    qDebug() << "Right " << mRight;
}

void Camera::updateForwardVector()
{
    mRight = gsl::Vector3D(1.f, 0.f, 0.f);
    mRight.rotateY(mYaw);
    mRight.normalize();
    mUp = gsl::Vector3D(0.f, 1.f, 0.f);
    mUp.rotateX(mPitch);
    mUp.normalize();
    mForward = mUp^mRight;

    updateRightVector();
}

void Camera::update()
{
    mYawMatrix.setToIdentity();
    mPitchMatrix.setToIdentity();

    mPitchMatrix.rotateX(mPitch);
    mYawMatrix.rotateY(mYaw);

    mPosition -= mForward * mSpeed;

    mViewMatrix = mPitchMatrix* mYawMatrix;
    mViewMatrix.translate(-mPosition);
}

void Camera::setPosition(const gsl::Vector3D &position)
{
    mPosition = position;
}

void Camera::setSpeed(float speed)
{
    mSpeed = speed;
}

void Camera::updateHeigth(float deltaHeigth)
{
    mPosition.y += deltaHeigth;
}

void Camera::moveRight(float delta)
{
    //This fixes a bug in the up and right calculations
    //so camera always holds its height when straifing
    //should be fixed thru correct right calculations!
    gsl::Vector3D right = mRight;
    right.y = 0.f;
    mPosition += right * delta;
}

gsl::Vector3D Camera::position() const
{
    return mPosition;
}

gsl::Vector3D Camera::up() const
{
    return mUp;
}

gsl::Vector3D Camera::forward() const
{
    return mForward;
}


Camera::Camera(QJsonObject Json)
{
    QJsonArray position = Json.take("position").toArray();
    mPosition.x = static_cast<float>(position.at(0).toDouble());
    mPosition.y = static_cast<float>(position.at(1).toDouble());
    mPosition.z = static_cast<float>(position.at(2).toDouble());
}

QJsonObject Camera::toJson()
{
    QJsonObject object;
    QJsonArray position;
    position.insert(0, static_cast<double>(mPosition.x));
    position.insert(1, static_cast<double>(mPosition.y));
    position.insert(2, static_cast<double>(mPosition.z));

    object.insert("position", position);
    return object;
}

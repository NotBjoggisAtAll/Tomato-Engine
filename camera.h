#ifndef CAMERA_H
#define CAMERA_H

#include "GSL/gsl_math.h"

class Camera
{
public:
    Camera() = default;
    Camera(gsl::Vector3D position);
    Camera(QJsonObject Json);

    void pitch(float degrees);
    void yaw(float degrees);
    void update();

    void setPosition(const gsl::Vector3D &position);

    void moveUp(float speed);
    void moveForward(float speed);
    void moveRight(float speed);

    gsl::Vector3D position() const;
    gsl::Vector3D up() const;
    gsl::Vector3D forward() const;

    gsl::Matrix4x4 viewMatrix_;
    gsl::Matrix4x4 projectionMatrix_;
    QJsonObject toJson();
    void fromJson(QJsonObject Json);

    void setSpeed(float value);
    float getSpeed() const;
private:
    void updateRightVector();
    void updateForwardVector();

    gsl::Vector3D forward_{0.f, 0.f, -1.f};
    gsl::Vector3D right_{1.f, 0.f, 0.f};
    gsl::Vector3D up_{0.f, 1.f, 0.f};

    gsl::Vector3D position_{0.f, 0.f, 0.f};
    float pitch_{0.f};
    float yaw_{0.f};

    float speed_{0.01f}; //camera will move by this speed along the mForward vector
    float rotateSpeed_{0.1f};
};

#endif // CAMERA_H

#ifndef CAMERA_H
#define CAMERA_H

#include "component.h"
#include <array>
#include "GSL/matrix4x4.h"

struct Plane
{
    float distance_;
    gsl::Vector3D normal_;
};

struct Camera : public Component
{
    Camera();
    Camera(bool isInUse);
    Camera(bool isInUse, float yaw, float pitch);
    Camera(float yaw, float pitch);
    Camera(QJsonObject Json);

    gsl::Matrix4x4 viewMatrix_;
    gsl::Matrix4x4 projectionMatrix_;

    gsl::Vector3D forward_{0.f, 0.f, -1.f};
    gsl::Vector3D right_{1.f, 0.f, 0.f};
    gsl::Vector3D up_{0.f, 1.f, 0.f};

    float yaw_{0.f};
    float pitch_{0.f};

    float speed_{0.01f}; //camera will move by this speed along the mForward vector
    float rotateSpeed_{0.1f};

    float aspectRatio_ = 0;
    float fieldOfView_ = 45.f;


    ///float is distance to origo, gsl::vector3D is normal.
    std::array<Plane, 6> frustum_; //left, right, top, bottom, farPlane, nearPlane

    bool isInUse_ = false;
    bool isEditor = false;
    virtual QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // CAMERA_H

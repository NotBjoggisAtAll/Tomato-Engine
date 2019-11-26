#ifndef CAMERA_H
#define CAMERA_H

#include "component.h"
#include <array>
#include "GSL/matrix4x4.h"

/**
 * A helper struct to easier calculate and show the frustum.
 */
struct Plane
{
    float distance_;
    gsl::Vector3D normal_;
};

/**
 * Camera component.
 */
struct Camera : public Component
{
    /**
     * Default constructor.
     */
    Camera() = default;

    /**
     * Constructor taking in a bool
     * @param isInUse - bool. Tells if the camera is in use.
     */
    Camera(bool isInUse);

    /**
     * Constructor taking in a bool and two floats.
     * @param isInUse - bool. Tells if the camera is in use.
     * @param yaw - float. The yaw of the camera.
     * @param pitch - float. The pitch of the camera.
     */
    Camera(bool isInUse, float yaw, float pitch);

    /**
     * Constructor taking in two floats.
     * @param yaw - float. The yaw of the camera.
     * @param pitch - float. The pitch of the camera.
     */
    Camera(float yaw, float pitch);

    /**
     * Constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Camera component with the data in the QJsonObject. If its the QJsonObject is not valid the component is constructed with default values.
     */
    Camera(QJsonObject Json);

    ///The camera's view matrix.
    gsl::Matrix4x4 viewMatrix_;

    ///The camera's projection matrix.
    gsl::Matrix4x4 projectionMatrix_;

    /// The camera's forward vector.
    gsl::Vector3D forward_{0.f, 0.f, -1.f};

    /// The camera's right vector.
    gsl::Vector3D right_{1.f, 0.f, 0.f};

    /// The camera's up vector.
    gsl::Vector3D up_{0.f, 1.f, 0.f};


    /// The camera's yaw rotation.
    float yaw_{0.f};

    /// The camera's pitch rotation.
    float pitch_{0.f};

    /// The speed the camera will move along its forward vector.
    float speed_{0.01f};

    /// The speed the camera will rotate it's yaw and pitch.
    float rotateSpeed_{0.1f};

    /// The camera's aspect ratio.
    float aspectRatio_ = 0;

    /// The camera's field of view.
    float fieldOfView_ = 45.f;


    /// The camera's frustum defined by 6 planes. Left, right, top bottom, near plane and far plane.
    std::array<Plane, 6> frustum_;

    /// If true the camera is currently in use.
    bool isInUse_ = false;

    /// If true the camera is an editor camera.
    bool isEditor = false;

    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    virtual QJsonObject toJson() override;
    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    virtual void fromJson(QJsonObject Json) override;
};

#endif // CAMERA_H

#include "camerasystem.h"
#include "GSL/matrix4x4.h"
#include "world.h"
#include "Components/camera.h"
#include "Components/transform.h"

CameraSystem::CameraSystem()
{

}


void CameraSystem::beginPlay()
{
}

void CameraSystem::tick()
{
    for(const auto& entity : entities_)
    {
        Camera* camera = getWorld()->getComponent<Camera>(entity).value();

        Transform* transform = getWorld()->getComponent<Transform>(entity).value();

        gsl::Matrix4x4 yawMatrix;
        gsl::Matrix4x4 pitchMatrix;

        pitchMatrix.rotateX(camera->pitch_);
        yawMatrix.rotateY(camera->yaw_);

        camera->viewMatrix_ = pitchMatrix * yawMatrix;

        if(camera->isInUse_)
        {
            transform->position_ -= camera->forward_ * camera->speed_;
            camera->viewMatrix_.translate(-transform->position_);
        }

        updateFrustum(camera);
    }
}

void CameraSystem::endPlay()
{
}

void CameraSystem::updateFrustum(Camera* camera)
{
    auto vpMatrix = camera->projectionMatrix_ * camera->viewMatrix_;

    gsl::Vector3D col1(vpMatrix[0], vpMatrix[2], vpMatrix[2]);
    gsl::Vector3D col2(vpMatrix[4], vpMatrix[5], vpMatrix[6]);
    gsl::Vector3D col3(vpMatrix[8], vpMatrix[9], vpMatrix[10]);
    gsl::Vector3D col4(vpMatrix[12], vpMatrix[13], vpMatrix[14]);

    camera->frustum_[0].normal_ = col4 + col1;
    camera->frustum_[1].normal_ = col4 - col1;
    camera->frustum_[2].normal_ = col4 - col2;
    camera->frustum_[3].normal_ = col4 + col2;
    camera->frustum_[4].normal_ = col4 - col3;
    camera->frustum_[5].normal_ = col3;
    camera->frustum_[0].distance_ = vpMatrix[15] + vpMatrix[3];
    camera->frustum_[1].distance_ = vpMatrix[15] - vpMatrix[3];
    camera->frustum_[2].distance_ = vpMatrix[15] - vpMatrix[7];
    camera->frustum_[3].distance_ = vpMatrix[15] + vpMatrix[7];
    camera->frustum_[4].distance_ = vpMatrix[15] - vpMatrix[11];
    camera->frustum_[5].distance_ = vpMatrix[11];
    for (unsigned int i = 0; i < 6; ++i) {
        float magnitude = 1.0f / camera->frustum_[i].normal_.length();
        camera->frustum_[i].normal_ = camera->frustum_[i].normal_ * magnitude;
        camera->frustum_[i].distance_ = camera->frustum_[i].distance_ * magnitude;
    }
}

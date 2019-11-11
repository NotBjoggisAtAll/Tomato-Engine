#include "rendersystem.h"

#include "world.h"
#include "Components/mesh.h"
#include "Components/transform.h"
#include "Components/material.h"
#include "Components/entitydata.h"
#include "Components/camera.h"
#include "shader.h"

void RenderSystem::beginPlay()
{
}

void RenderSystem::tick()
{
    initializeOpenGLFunctions();

    totalVerticeCount = 0;

    for(auto& entity : entities_)
    {
        auto mesh = getWorld()->getComponent<Mesh>(entity).value();

        if(!mesh->isVisible_)
            continue;

        auto material = getWorld()->getComponent<Material>(entity).value();
        auto transform = getWorld()->getComponent<Transform>(entity).value();

        if(!sphereInsideFrustum(transform->position_, 1) && mesh->isAffectedByFrustum_) continue;



        glUseProgram(material->shader_->getProgram());
        glBindVertexArray(mesh->VAO_);

        gsl::Matrix4x4 modelMatrix;

        if(mesh->filepath_ == "frustum")
        {
            Camera* camera = getWorld()->getComponent<Camera>(entity).value();
            gsl::Matrix4x4 inverseView = camera->viewMatrix_;
            inverseView.inverse();
            gsl::Matrix4x4 inverseProjection = camera->projectionMatrix_;
            inverseProjection.inverse();

            modelMatrix = inverseView * inverseProjection;
        }
        else
        {
            gsl::Matrix4x4 posMatrix;
            posMatrix.setPosition(transform->position_);

            gsl::Matrix4x4 rotMatrix;
            rotMatrix.rotateX(transform->rotation_.x);
            rotMatrix.rotateY(transform->rotation_.y);
            rotMatrix.rotateZ(transform->rotation_.z);

            gsl::Matrix4x4 scaleMatrix;
            scaleMatrix.scale(transform->scale_);

            modelMatrix = posMatrix * rotMatrix * scaleMatrix;
        }

        material->shader_->transmitUniformData(&modelMatrix, material);

        totalVerticeCount += mesh->verticeCount_;

        if(mesh->indiceCount_ > 0)
            glDrawElements(mesh->drawType_, mesh->indiceCount_, GL_UNSIGNED_INT, nullptr);

        else
            glDrawArrays(mesh->drawType_, 0, mesh->verticeCount_);

    }
}

bool RenderSystem::sphereInsideFrustum(const gsl::Vector3D vecCenter, float radius)
{
    const auto& frustum = getWorld()->getComponent<Camera>(getWorld()->getCurrentCamera()).value()->frustum_;
    for(unsigned int i = 0; i < 6; i++)
    {
        if(gsl::Vector3D::dot(vecCenter, frustum[i].normal_) + frustum[i].distance_ + radius <= 0)
            return false;
    }
    return true;
}

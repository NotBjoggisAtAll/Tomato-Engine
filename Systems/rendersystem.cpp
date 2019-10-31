#include "rendersystem.h"

#include "world.h"
#include "Components/mesh.h"
#include "Components/transform.h"
#include "Components/material.h"
#include "Components/entitydata.h"
#include "shader.h"

void RenderSystem::beginPlay()
{
}

void RenderSystem::tick()
{
    initializeOpenGLFunctions();

    for(auto& entity : entities_)
    {
        auto mesh = getWorld()->getComponent<Mesh>(entity).value();

        if(!mesh->isVisible_)
            continue;

        auto material = getWorld()->getComponent<Material>(entity).value();
        auto transform = getWorld()->getComponent<Transform>(entity).value();

        glUseProgram(material->shader_->getProgram());
        glBindVertexArray(mesh->VAO_);

        gsl::Matrix4x4 posMatrix;
        posMatrix.setPosition(transform->position_);

        gsl::Matrix4x4 rotMatrix;
        rotMatrix.rotateX(transform->rotation_.x);
        rotMatrix.rotateY(transform->rotation_.y);
        rotMatrix.rotateZ(transform->rotation_.z);

        gsl::Matrix4x4 scaleMatrix;
        scaleMatrix.scale(transform->scale_);

        gsl::Matrix4x4 modelMatrix;
        modelMatrix = posMatrix * rotMatrix * scaleMatrix;

        material->shader_->transmitUniformData(&modelMatrix, material);


        if(mesh->indiceCount_ > 0)
            glDrawElements(mesh->drawType_, mesh->indiceCount_, GL_UNSIGNED_INT, nullptr);

        else
            glDrawArrays(mesh->drawType_, 0, mesh->verticeCount_);
    }
}

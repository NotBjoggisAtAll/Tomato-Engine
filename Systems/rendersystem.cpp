#include "rendersystem.h"

#include "World.h"
#include "Components/meshcomponent.h"
#include "Components/transformcomponent.h"
#include "Components/materialcomponent.h"
#include "Components/entitydata.h"
#include "shader.h"

RenderSystem::RenderSystem()
{
    world = getWorld();
}

void RenderSystem::render()
{
    initializeOpenGLFunctions();

    for(auto& entity : mEntities)
    {
        auto mesh = world->getComponent<Mesh>(entity).value();

        if(!mesh->isVisible)
            continue;

        auto material = world->getComponent<Material>(entity).value();
        auto transform = world->getComponent<Transform>(entity).value();

        glUseProgram(material->mShader->getProgram());
        glBindVertexArray(mesh->mVAO);

        gsl::Matrix4x4 posMatrix;
        posMatrix.setPosition(transform->position);

        gsl::Matrix4x4 rotMatrix;
        rotMatrix.rotateX(transform->rotation.x);
        rotMatrix.rotateY(transform->rotation.y);
        rotMatrix.rotateZ(transform->rotation.z);

        gsl::Matrix4x4 scaleMatrix;
        scaleMatrix.scale(transform->scale);

        gsl::Matrix4x4 modelMatrix;
        modelMatrix = posMatrix * rotMatrix * scaleMatrix;

        material->mShader->transmitUniformData(&modelMatrix, material);


        if(mesh->mIndiceCount > 0)
            glDrawElements(mesh->mDrawType, mesh->mIndiceCount, GL_UNSIGNED_INT, nullptr);

        else
            glDrawArrays(mesh->mDrawType, 0, mesh->mVerticeCount);
    }
}

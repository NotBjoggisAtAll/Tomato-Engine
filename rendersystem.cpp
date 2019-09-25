#include "rendersystem.h"

#include "World.h"
#include "Components/meshcomponent.h"
#include "Components/transformcomponent.h"
#include "Components/materialcomponent.h"
#include "shader.h"

RenderSystem::RenderSystem()
{
    world = World::getWorld();
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
        material->mShader->transmitUniformData(&transform->mMatrix, material);

        if(mesh->mIndiceCount > 0)
            glDrawElements(mesh->mDrawType, mesh->mIndiceCount, GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(mesh->mDrawType, 0, mesh->mVerticeCount);

    }
}

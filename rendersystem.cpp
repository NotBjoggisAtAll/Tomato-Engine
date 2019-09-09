#include "rendersystem.h"
#include "gameobject.h"
#include "shader.h"
#include "resourcemanager.h"
RenderSystem::RenderSystem()
{
    factory = ResourceManager::instance();
}

void RenderSystem::Render()
{
    initializeOpenGLFunctions();
    for(auto& Component : factory->mMeshComponents)
    {
        auto Material = factory->mMaterialComponents.at(Component.EntityID);
        auto Transform = factory->mTransformComponents.at(Component.EntityID);

        glUseProgram(Material.mShader->getProgram());
        glBindVertexArray(Component.mVAO );
        Material.mShader->transmitUniformData(&Transform.mMatrix, &Material);   //rendersystem should know what data is needed for each shader.

        //checking if indices are used - draws accordingly with Elements or Arrays
        if (Component.mIndiceCount > 0)
            glDrawElements(Component.mDrawType, Component.mIndiceCount, GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(Component.mDrawType, 0, Component.mVerticeCount);
    }
}

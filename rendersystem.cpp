#include "rendersystem.h"
#include "shader.h"
#include "resourcemanager.h"
RenderSystem::RenderSystem()
{
    Factory = ResourceManager::instance();
}

void RenderSystem::Render()
{
    initializeOpenGLFunctions();
    for(auto& Component : Factory->mMeshComponents)
    {
        if(!Component.isVisible)
            continue;
        auto Material = Factory->getMaterialComponent(Component.EntityID);
        auto Transform = Factory->getTransformComponent(Component.EntityID);
        auto Parent = Transform->mParent;



        glUseProgram(Material->mShader->getProgram());
        glBindVertexArray(Component.mVAO );
        if(Parent)
        {

            gsl::Matrix4x4* transformMatrix = new gsl::Matrix4x4(Parent->mMatrix * Transform->mMatrix);

            Material->mShader->transmitUniformData(transformMatrix, Material);   //rendersystem should know what data is needed for each shader.
        }
        else{
            Material->mShader->transmitUniformData(&Transform->mMatrix, Material);   //rendersystem should know what data is needed for each shader.

        }

        //checking if indices are used - draws accordingly with Elements or Arrays
        if (Component.mIndiceCount > 0)
            glDrawElements(Component.mDrawType, Component.mIndiceCount, GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(Component.mDrawType, 0, Component.mVerticeCount);
    }
}

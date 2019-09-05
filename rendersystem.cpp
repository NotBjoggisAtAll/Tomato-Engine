#include "rendersystem.h"
#include "gameobject.h"
#include "shader.h"
#include "resourcefactory.h"
RenderSystem::RenderSystem()
{

}

void RenderSystem::Render()
{
    initializeOpenGLFunctions();
    for(auto& Component : ResourceFactory::instance()->GetComponents())
    {

        glUseProgram(Component.Owner->mMaterialComponent->mShader->getProgram());
        glBindVertexArray(Component.mVAO );
        Component.Owner->mMaterialComponent->mShader->transmitUniformData(&Component.Owner->mTransformComponent->mMatrix, Component.Owner->mMaterialComponent);   //rendersystem should know what data is needed for each shader.

        //checking if indices are used - draws accordingly with Elements or Arrays
        if (Component.mIndiceCount > 0)
            glDrawElements(Component.mDrawType, Component.mIndiceCount, GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(Component.mDrawType, 0, Component.mVerticeCount);
    }
}

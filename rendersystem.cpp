#include "rendersystem.h"
#include "gameobject.h"
#include "shader.h"
#include "resourcefactory.h"
RenderSystem::RenderSystem()
{
    factory = ResourceFactory::instance();
}

void RenderSystem::Render()
{
    initializeOpenGLFunctions();
    for(auto& Component : factory->getMeshComponents())
    {
        auto Material = factory->getMaterialComponents().at(Component.EntityID);
        auto Transform = factory->getTransformComponents().at(Component.EntityID);

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

#include "rendersystem.h"
#include "Components/rendercomponent.h"
#include "gameobject.h"
#include "shader.h"
RenderSystem::RenderSystem()
{

}

void RenderSystem::Init()
{
    for (auto& Component : mComponents) {

        if (!Component.Owner->mMeshComponent) continue;

        //must call this to use OpenGL functions
        initializeOpenGLFunctions();

        //Vertex Array Object - VAO
        glGenVertexArrays( 1, &Component.mVAO );
        glBindVertexArray(Component.mVAO);

        //Vertex Buffer Object to hold vertices - VBO
        glGenBuffers( 1, &Component.mVBO );
        glBindBuffer( GL_ARRAY_BUFFER, Component.mVBO );

        glBufferData( GL_ARRAY_BUFFER, Component.Owner->mMeshComponent->mVertices.size()*sizeof(Vertex), Component.Owner->mMeshComponent->mVertices.data(), GL_STATIC_DRAW );

        // 1rst attribute buffer : vertices
        glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
        glEnableVertexAttribArray(0);

        // 2nd attribute buffer : colors
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(1);

        // 3rd attribute buffer : uvs
        glVertexAttribPointer(2, 2,  GL_FLOAT, GL_FALSE, sizeof( Vertex ), (GLvoid*)( 6 * sizeof( GLfloat ) ));
        glEnableVertexAttribArray(2);

        //Second buffer - holds the indices (Element Array Buffer - EAB):
        glGenBuffers(1, &Component.mEAB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Component.mEAB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Component.Owner->mMeshComponent->mIndices.size() * sizeof(GLuint), Component.Owner->mMeshComponent->mIndices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
}

void RenderSystem::Render()
{
    for (auto& Component : mComponents) {
        auto o = Component.Owner;
        if(!(o->mMeshComponent || o->mMaterialComponent || o->mTransformComponent)) continue;

        glUseProgram(o->mMaterialComponent->mShader->getProgram());
        glBindVertexArray( Component.mVAO );
        o->mMaterialComponent->mShader->transmitUniformData(&o->mTransformComponent->mMatrix, o->mMaterialComponent);
        glDrawElements(GL_TRIANGLES, o->mMeshComponent->mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}

RenderComponent *RenderSystem::CreateComponent(GameObject* Owner)
{
    auto& Component = mComponents.emplace_back(RenderComponent());
    Component.Owner = Owner;
    return &Component;
}

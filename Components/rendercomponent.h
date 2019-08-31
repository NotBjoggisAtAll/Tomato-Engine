#ifndef RENDER_H
#define RENDER_H

#include "component.h"
#include "meshcomponent.h"
#include "materialcomponent.h"
#include "transformcomponent.h"
#include <QOpenGLFunctions_4_1_Core>

struct RenderComponent : public Component, public QOpenGLFunctions_4_1_Core
{
    RenderComponent(MeshComponent* MeshComponent = nullptr, MaterialComponent* MaterialComponent = nullptr, TransformComponent* TransformComponent = nullptr)
        : mMeshComponent(MeshComponent), mMaterialComponent(MaterialComponent), mTransformComponent(TransformComponent) {}
    ~RenderComponent()
    {
        mMeshComponent = nullptr;
        mMaterialComponent = nullptr;
    }

    void Init()
    {
        if(mMeshComponent == nullptr)
        {
            qDebug() << "MeshComponent do not exist!";
            return;
        }

        //must call this to use OpenGL functions
        initializeOpenGLFunctions();

        //Vertex Array Object - VAO
        glGenVertexArrays( 1, &mVAO );
        glBindVertexArray( mVAO );

        //Vertex Buffer Object to hold vertices - VBO
        glGenBuffers( 1, &mVBO );
        glBindBuffer( GL_ARRAY_BUFFER, mVBO );

        glBufferData( GL_ARRAY_BUFFER, mMeshComponent->mVertices.size()*sizeof(Vertex), mMeshComponent->mVertices.data(), GL_STATIC_DRAW );

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
        glGenBuffers(1, &mEAB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEAB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMeshComponent->mIndices.size() * sizeof(GLuint), mMeshComponent->mIndices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
    }
    void Render()
    {
        if(mMaterialComponent == nullptr)
        {
            qDebug() << "MaterialComponent do not exist!";
            return;
        }

        glUseProgram(mMaterialComponent->mShader->getProgram());
        glBindVertexArray( mVAO );
        mMaterialComponent->mShader->transmitUniformData(&mTransformComponent->mMatrix, mMaterialComponent);
        glDrawElements(GL_TRIANGLES, mMeshComponent->mIndices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    MeshComponent* mMeshComponent{nullptr};
    MaterialComponent* mMaterialComponent{nullptr};
    TransformComponent* mTransformComponent{nullptr};

    GLuint mVAO{0};
    GLuint mVBO{0};
    GLuint mEAB{0}; //holds the indices (Element Array Buffer - EAB)
};

#endif // RENDER_H

#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex.h"
#include "matrix4x4.h"
#include "material.h"
#include "shader.h"

class RenderWindow;

class VisualObject : public QOpenGLFunctions_4_1_Core {
public:
    VisualObject();
    virtual ~VisualObject();
    virtual void init();
    virtual void draw()=0;

    gsl::Matrix4x4 mMatrix;

    void setShader(Shader *shader);

    std::string mName;

    RenderWindow *mRenderWindow; //Just to be able to call checkForGLerrors()

    MaterialComponent mMaterial;

protected:

std::vector<Vertex> mVertices;
std::vector<unsigned int> mIndices;

    GLuint mVAO{0};
    GLuint mVBO{0};
    GLuint mEAB{0}; //holds the indices (Element Array Buffer - EAB)

};
#endif // VISUALOBJECT_H


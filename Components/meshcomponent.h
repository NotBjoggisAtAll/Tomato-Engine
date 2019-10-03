#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "gltypes.h"

struct Mesh
{
    GLuint mVAO{0};
    GLuint mVBO{0};
    GLuint mEAB{0};

    GLuint mVerticeCount{0};
    GLuint mIndiceCount{0};
    GLenum mDrawType{0};

    bool isVisible{true};
};

#endif // MESHCOMPONENT_H

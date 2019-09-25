#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

struct Mesh
{
    GLuint mVAO{0};
    GLuint mVBO{0};
    GLuint mEAB{0};

    GLint mVerticeCount{0};
    GLint mIndiceCount{0};
    GLenum mDrawType{0};

    bool isVisible{true};
};

#endif // MESHCOMPONENT_H

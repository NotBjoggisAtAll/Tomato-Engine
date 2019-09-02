#ifndef RENDER_H
#define RENDER_H

#include "component.h"
class GameObject;

struct RenderComponent : public Component
{
    RenderComponent(){}
    GLuint mVAO{0};
    GLuint mVBO{0};
    GLuint mEAB{0}; //holds the indices (Element Array Buffer - EAB)
};

#endif // RENDER_H

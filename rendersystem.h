#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>

class RenderComponent;
class GameObject;

struct RenderSystem : public QOpenGLFunctions_4_1_Core
{
    RenderSystem();
    void Render();

};

#endif // RENDERSYSTEM_H

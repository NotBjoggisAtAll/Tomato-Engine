#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>

class RenderComponent;
class GameObject;
class ResourceFactory;

struct RenderSystem : public QOpenGLFunctions_4_1_Core
{
    RenderSystem();
    void Render();

    ResourceFactory* factory{nullptr};

};

#endif // RENDERSYSTEM_H

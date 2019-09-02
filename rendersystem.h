#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <QOpenGLFunctions_4_1_Core>

class RenderComponent;
class GameObject;

class RenderSystem : public QOpenGLFunctions_4_1_Core
{
public:
    RenderSystem();
    void Init();
    void Render();

    RenderComponent* CreateComponent(GameObject *Owner);

    std::vector<RenderComponent> mComponents;
};

#endif // RENDERSYSTEM_H

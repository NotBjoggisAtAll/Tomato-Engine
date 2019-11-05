#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include "texture.h"
#include "camera.h"
#include "types.h"
#include <memory>

class QOpenGLContext;
class QOpenGLDebugLogger;

class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow();
    ~RenderWindow() override;

    QOpenGLContext *context() { return context_; }

    void toggleWireframe();

    void checkForGLerrors();

    void makeCollisionBorder(Entity newEntity);

    void tick();
    void setCamera(Camera* newCamera);

signals:
    void updateCameraPerspectives(float aspectRatio);
    void initDone();

private:
    void init();
    void exposeEvent(QExposeEvent *) override;

    QOpenGLContext *context_{nullptr};
    void startOpenGLDebugger();
    QOpenGLDebugLogger* openGLDebugLogger_{nullptr};

    bool initialized_{false};
    bool wireframe_{false};

    Texture *texture_[4]{nullptr}; //We can hold 4 textures
    
    Entity lastCollisionEntity = -1;
};

#endif // RENDERWINDOW_H

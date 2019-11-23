#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include "types.h"
#include <QOpenGLFunctions_4_1_Core>
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

    void tick(float deltaTime);

signals:
    void updateCameraPerspectives(float aspectRatio);
    void initDone();
public slots:
    void callExposeEvent();
private:
    void init();
    void exposeEvent(QExposeEvent *) override;

    QOpenGLContext *context_{nullptr};
    void startOpenGLDebugger();
    QOpenGLDebugLogger* openGLDebugLogger_{nullptr};

    bool initialized_{false};
    bool wireframe_{false};
    
    Entity lastCollisionEntity = -1;
};

#endif // RENDERWINDOW_H

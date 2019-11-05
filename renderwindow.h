#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include "texture.h"
#include "camera.h"
#include "types.h"
#include <memory>

class QOpenGLContext;
class Shader;
class MainWindow;

class EntityManager;

/// This inherits from QWindow to get access to the Qt functionality and
/// OpenGL surface.
/// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
/// This is the same as using glad and glw from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(MainWindow *mainWindow);
    ~RenderWindow() override;

    QOpenGLContext *context() { return context_; }

    void exposeEvent(QExposeEvent *) override;
    void toggleWireframe();

    void checkForGLerrors();

    void updateCollisionOutline(Entity newEntity);

    void tick();
    void updateCamera(Camera* newCamera);

signals:
    void updateCameraPerspectives(float aspectRatio);
    void initDone();

private:

    QString fileToLoad_ = "";

    void init();

    QOpenGLContext *context_{nullptr};
    bool initialized_{false};

    Texture *texture_[4]{nullptr}; //We can hold 4 textures



    bool mWireframe{false};






    MainWindow *mMainWindow{nullptr};    //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};


    void startOpenGLDebugger();


    std::chrono::high_resolution_clock::time_point mLastTime;
    
    Entity lastEntityCollision = -1;

};

#endif // RENDERWINDOW_H

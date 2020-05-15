#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include "types.h"
#include <QOpenGLFunctions_4_1_Core>
#include <memory>

class QOpenGLContext;
class QOpenGLDebugLogger;

/**
 * The RenderWindow is the window containing all OpenGL stuff. Often called the ViewPort.
 */
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    /**
     * Default constructor.
     * Sets up the window context.
     */
    RenderWindow();

    /**
     * Toggles between normal and wireframe mode. Called from MainWindow.
     */
    void toggleWireframe();

    /**
     * Creates an AABB box around a object when selected. Used to highlight which object you clicked.
     * @param newEntity - Entity. Entity clicked.
     */
    void makeCollisionBorder(Entity newEntity);

    /**
     * Runs every frame. Updates the RenderSystems. Is called by App's tick.
     * @param deltaTime - float.
     */
    void tick(float deltaTime);

signals:
    /**
     * Called whevener the screen is exposed (exposeEvent runs).
     * @param aspectRatio - The window's aspect ratio.
     */
    void updateCameraPerspectives(float aspectRatio);

    /**
     * Called when RenderWindow is done setting up. Calls App's postInit.
     */
    void initDone();
public slots:

    /**
     * Calles the ExposeEvent when world needs to update the camera perspectives.
     */
    void callExposeEvent();
private:

    /**
     * Initializing the rest of RenderWindow.
     */
    void init();

    /**
     * Called when the window is exposed to the screen or when the size is changed.
     * The first time this is called it calls the init function.
     */
    void exposeEvent(QExposeEvent *) override;

    /**
     * Function used to check GL errors.
     */
    void checkForGLerrors();

    /**
     * Function used to check GL errors.
     */
    void startOpenGLDebugger();

    /// The openGL context.
    QOpenGLContext *context_ = nullptr;

    /// The openGL debug logger.
    QOpenGLDebugLogger* openGLDebugLogger_ = nullptr;

    /// Used to check if init has run or not.
    bool initialized_ = false;

    /// Used to check if you're in wireframe mode or not.
    bool wireframe_ = false;
    
    /// The last entity that had a collisionbox around itself.
    Entity lastCollisionEntity = -1;
};

#endif // RENDERWINDOW_H

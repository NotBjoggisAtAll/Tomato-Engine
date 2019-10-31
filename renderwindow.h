#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include "texture.h"
#include "camera.h"
#include "input.h"
#include <QElapsedTimer>
#include "types.h"
#include <memory>

class QOpenGLContext;
class Shader;
class MainWindow;
class SoundSystem;
class MovementSystem;
class CollisionSystem;
class SceneSystem;
class ScriptSystem;

class EntityManager;

class ResourceFactory;
class World;

class RenderSystem;
/// This inherits from QWindow to get access to the Qt functionality and
/// OpenGL surface.
/// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
/// This is the same as using glad and glw from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;
    void toggleWireframe();

    void checkForGLerrors();


    std::shared_ptr<RenderSystem> mRenderSystem;
    std::shared_ptr<MovementSystem> mMovementSystem;
    std::shared_ptr<SoundSystem> mSoundSystem;
    std::shared_ptr<CollisionSystem> mCollisionSystem;
    std::shared_ptr<SceneSystem> mSceneSystem;
    std::shared_ptr<ScriptSystem> scriptSystem_;

    World* world;
    ResourceFactory* resourceFactory;


    std::vector<Entity> entities;

public slots:
    void recieveJsonPath(QString JsonPath);
    void newScene(QString sceneName);
private slots:
    void render();


    void spawnObject(std::string name, std::string path);

    void playGame();
    void stopGame();
    Entity createEntity();
private:

    QString fileToLoad_ = "";

    void init();
    void setCameraSpeed(float value);

    QOpenGLContext *mContext{nullptr};
    bool mInitialized{false};

    Texture *mTexture[4]{nullptr}; //We can hold 4 textures

    Camera *mCurrentCamera{nullptr};
    Camera* mEditorCamera = nullptr;
    Camera *mGameCamera{nullptr};

    bool mWireframe{false};

    Input mInput;
    float mCameraSpeed{0.01f};
    float mCameraRotateSpeed{0.1f};
    int mMouseXlast{0};
    int mMouseYlast{0};

    QTimer *mRenderTimer{nullptr};  //timer that drives the gameloop
    QElapsedTimer mTimeStart;       //time variable that reads the actual FPS

    float mAspectratio{1.f};

    MainWindow *mMainWindow{nullptr};    //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};

    void calculateFramerate();

    void startOpenGLDebugger();

    void handleInput();

    std::chrono::high_resolution_clock::time_point mLastTime;

    void raycastFromMouse(QMouseEvent *event);
    void updateCamera(Camera* newCamera);
    
    void updateCollisionOutline(Entity newEntity);
    Entity lastEntityCollision = -1;
protected:
    //The QWindow that we inherit from has these functions to capture
    // mouse and keyboard. Uncomment to use
    //
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // RENDERWINDOW_H

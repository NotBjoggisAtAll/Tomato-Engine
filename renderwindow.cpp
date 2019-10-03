#include "renderwindow.h"
#include <QTimer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <chrono>

#include "mainwindow.h"

#include "colorshader.h"
#include "textureshader.h"
#include "phongshader.h"

#include "Systems/rendersystem.h"
#include "Systems/soundsystem.h"
#include "Systems/movementsystem.h"

#include "Managers/entitymanager.h"
#include "Managers/shadermanager.h"
#include "Managers/soundmanager.h"
#include "Components/allcomponents.h"

#include "resourcefactory.h"
#include "World.h"
#include "constants.h"

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow)
{
    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    mContext = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);
}

RenderWindow::~RenderWindow()
{
    SoundManager::instance()->cleanUp();
}

/// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init()
{
    //Connect the gameloop timer to the render function:
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));

    connect(mMainWindow, &MainWindow::spawnObject, this, &RenderWindow::spawnObject);


    //********************** General OpenGL stuff **********************

    //The OpenGL context has to be set.
    //The context belongs to the instanse of this class!
    if (!mContext->makeCurrent(this)) {
        qDebug() << "makeCurrent() failed";
        return;
    }

    //just to make sure we don't init several times
    //used in exposeEvent()
    if (!mInitialized)
        mInitialized = true;

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Print render version info:
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

    //Start the Qt OpenGL debugger
    //Really helpfull when doing OpenGL
    //Supported on most Windows machines
    //reverts to plain glGetError() on Mac and other unsupported PCs
    // - can be deleted
    startOpenGLDebugger();

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);    //enables depth sorting - must use GL_DEPTH_BUFFER_BIT in glClear
    glEnable(GL_CULL_FACE);     //draws only front side of models - usually what you want -
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //color used in glClear GL_COLOR_BUFFER_BIT



    //**********************  Texture stuff: **********************

    mTexture[0] = new Texture("white.bmp");
    mTexture[1] = new Texture("hund.bmp", 1);
    mTexture[2] = new Texture("skybox.bmp", 2);


    //Set the textures loaded to a texture unit
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture[0]->id());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTexture[1]->id());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mTexture[2]->id());

    //********************** Creating Systems *********************

    world = getWorld();

    resourceFactory = ResourceFactory::instance();

    world->registerComponent<Transform>();
    world->registerComponent<Mesh>();
    world->registerComponent<Material>();
    world->registerComponent<Sound>();
    world->registerComponent<EntityData>();
    world->registerComponent<Light>();

    mRenderSystem = world->registerSystem<RenderSystem>();
    mSoundSystem = world->registerSystem<SoundSystem>();
    mMovementSystem = world->registerSystem<MovementSystem>();

    // Setter opp hvilke komponenter de ulike systemene trenger
    Signature renderSign;
    renderSign.set(world->getComponentType<Transform>());
    renderSign.set(world->getComponentType<Mesh>());
    renderSign.set(world->getComponentType<Material>());
    world->setSystemSignature<RenderSystem>(renderSign);

    Signature soundSign;
    soundSign.set(world->getComponentType<Transform>());
    soundSign.set(world->getComponentType<Sound>());
    world->setSystemSignature<SoundSystem>(soundSign);

    Signature movementSign;
    movementSign.set(world->getComponentType<Transform>());
    movementSign.set(world->getComponentType<EntityData>());
    world->setSystemSignature<MovementSystem>(movementSign);

    //********************** Making the objects to be drawn **********************

    Entity entity = world->createEntity();

    world->addComponent(entity, EntityData("Axis"));
    world->addComponent(entity, resourceFactory->loadMesh("axis"));
    world->addComponent(entity, Transform());
    world->addComponent(entity, Material(ShaderManager::instance()->colorShader()));

    entity = world->createEntity();

    world->addComponent(entity, EntityData("Skybox"));
    world->addComponent(entity, resourceFactory->loadMesh("skybox"));
    world->addComponent(entity, Transform());
    world->addComponent(entity, Material(ShaderManager::instance()->textureShader(),2));

    auto transform = world->getComponent<Transform>(entity).value();
    transform->scale = {15.f,15.f,15.f};

    entity = world->createEntity();

    world->addComponent(entity, EntityData("Box"));
    world->addComponent(entity, resourceFactory->loadMesh(gsl::meshFilePath + "box2.txt"));
    world->addComponent(entity, Material(ShaderManager::instance()->colorShader()));
    world->addComponent(entity, Transform());

    transform = world->getComponent<Transform>(entity).value();
    transform->rotation.y = 180.f;


    entity = world->createEntity();

    world->addComponent(entity, EntityData("Monkey"));
    world->addComponent(entity, resourceFactory->loadMesh(gsl::meshFilePath + "monkey.obj"));
    world->addComponent(entity, Material(ShaderManager::instance()->phongShader()));
    world->addComponent(entity, Transform());

    transform = world->getComponent<Transform>(entity).value();
    transform->scale = {0.5f, 0.5f, 0.5f};
    transform->position = {3.f, 2.f, -2.f};

    entity = world->createEntity();

    world->addComponent(entity, EntityData("Sound Source"));
    world->addComponent(entity, Transform());
    world->addComponent(entity, Sound(SoundManager::instance()->createSource("Caravan",{}, "caravan_mono.wav", true, .5f)));


    entity = world->createEntity();

    world->addComponent(entity, EntityData("Light Source"));
    world->addComponent(entity, Transform({2.5f, 3.f, 0.f},{},{0.5f,0.5f,0.5f}));
    world->addComponent(entity, Light());
    world->addComponent(entity, Material(ShaderManager::instance()->textureShader(),{1},0));
    world->addComponent(entity, resourceFactory->loadMesh(gsl::meshFilePath + "box2.txt"));
    ShaderManager::instance()->phongShader()->setLight(entity);

    //********************** System stuff **********************

    mMainWindow->DisplayEntitesInOutliner();

    //********************** Set up camera **********************
    mCurrentCamera = new Camera();
    mCurrentCamera->setPosition(gsl::Vector3D(1.f, 1.f, 4.4f));
    //    mCurrentCamera->yaw(45.f);
    //    mCurrentCamera->pitch(5.f);

    //new system - shader sends uniforms so needs to get the view and projection matrixes from camera
    for(auto& Shader : ShaderManager::instance()->mShaders){
        Shader->setCurrentCamera(mCurrentCamera);
    }
}

///Called each frame - doing the rendering
void RenderWindow::render()
{
    //calculate the time since last render-call
    //this should be the same as xxx in the mRenderTimer->start(xxx) set in RenderWindow::exposeEvent(...)
    //    auto now = std::chrono::high_resolution_clock::now();
    //    std::chrono::duration<float> duration = now - mLastTime;
    //    std::cout << "Chrono deltaTime " << duration.count()*1000 << " ms" << std::endl;
    //    mLastTime = now;

    //input
    handleInput();

    mCurrentCamera->update();

    mSoundSystem->update(mCurrentCamera);


    mTimeStart.restart(); //restart FPS clock
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)

    //to clear the screen for each redraw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    mRenderSystem->render();

    //Calculate framerate before
    // checkForGLerrors() because that takes a long time
    // and before swapBuffers(), else it will show the vsync time
    calculateFramerate();


    mContext->swapBuffers(this);

}

void RenderWindow::setCameraSpeed(float value)
{
    mCameraSpeed += value;

    //Keep within min and max values
    if(mCameraSpeed < 0.01f)
        mCameraSpeed = 0.01f;
    if (mCameraSpeed > 0.3f)
        mCameraSpeed = 0.3f;
}

void RenderWindow::spawnObject(std::string name, std::string path)
{
    auto entity = world->createEntity();

    world->addComponent(entity, EntityData(name));
    world->addComponent(entity, resourceFactory->loadMesh(path));
    world->addComponent(entity,Transform());
    world->addComponent(entity, Material(ShaderManager::instance()->colorShader()));

    mMainWindow->addEntityToUi(entity);
}

//    temp = new BillBoard();
//    temp->init();
//    temp->setShader(ShaderManager::instance()->textureShader());
//    temp->mMatrix.translate(4.f, 0.f, -3.5f);
//    temp->mName = "Billboard";
//    temp->mRenderWindow = this;
//    temp->mMaterial.mTextureUnit = 1;
//    temp->mMaterial.mColor = gsl::Vector3D(0.7f, 0.6f, 0.1f);
//    dynamic_cast<BillBoard*>(temp)->setConstantYUp(true);
//    mVisualObjects.push_back(temp);

void RenderWindow::handleInput()
{
    //Camera
    mCurrentCamera->setSpeed(0.f);  //cancel last frame movement
    if(mInput.RMB)
    {
        if(mInput.W)
            mCurrentCamera->setSpeed(-mCameraSpeed);
        if(mInput.S)
            mCurrentCamera->setSpeed(mCameraSpeed);
        if(mInput.D)
            mCurrentCamera->moveRight(mCameraSpeed);
        if(mInput.A)
            mCurrentCamera->moveRight(-mCameraSpeed);
        if(mInput.Q)
            mCurrentCamera->updateHeigth(-mCameraSpeed);
        if(mInput.E)
            mCurrentCamera->updateHeigth(mCameraSpeed);
    }
    else
    {
        //        if(mInput.W)
        //            mLight->mMatrix.translateZ(-mCameraSpeed);
        //        if(mInput.S)
        //            mLight->mMatrix.translateZ(mCameraSpeed);
        //        if(mInput.D)
        //            mLight->mMatrix.translateX(mCameraSpeed);
        //        if(mInput.A)
        //            mLight->mMatrix.translateX(-mCameraSpeed);
        //        if(mInput.Q)
        //            mLight->mMatrix.translateY(mCameraSpeed);
        //        if(mInput.E)
        //            mLight->mMatrix.translateY(-mCameraSpeed);
    }
}

void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    //    You get the keyboard input like this
    if(event->key() == Qt::Key_W)
    {
        mInput.W = true;
    }
    if(event->key() == Qt::Key_S)
    {
        mInput.S = true;
    }
    if(event->key() == Qt::Key_D)
    {
        mInput.D = true;
    }
    if(event->key() == Qt::Key_A)
    {
        mInput.A = true;
    }
    if(event->key() == Qt::Key_Q)
    {
        mInput.Q = true;
    }
    if(event->key() == Qt::Key_E)
    {
        mInput.E = true;
    }
    if(event->key() == Qt::Key_Z)
    {
    }
    if(event->key() == Qt::Key_X)
    {
    }
    if(event->key() == Qt::Key_Up)
    {
        mInput.UP = true;
    }
    if(event->key() == Qt::Key_Down)
    {
        mInput.DOWN = true;
    }
    if(event->key() == Qt::Key_Left)
    {
        mInput.LEFT = true;
    }
    if(event->key() == Qt::Key_Right)
    {
        mInput.RIGHT = true;
    }
    if(event->key() == Qt::Key_U)
    {
    }
    if(event->key() == Qt::Key_O)
    {
    }
}

void RenderWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        mInput.W = false;
    }
    if(event->key() == Qt::Key_S)
    {
        mInput.S = false;
    }
    if(event->key() == Qt::Key_D)
    {
        mInput.D = false;
    }
    if(event->key() == Qt::Key_A)
    {
        mInput.A = false;
    }
    if(event->key() == Qt::Key_Q)
    {
        mInput.Q = false;
    }
    if(event->key() == Qt::Key_E)
    {
        mInput.E = false;
    }
    if(event->key() == Qt::Key_Z)
    {
    }
    if(event->key() == Qt::Key_X)
    {
    }
    if(event->key() == Qt::Key_Up)
    {
        mInput.UP = false;
    }
    if(event->key() == Qt::Key_Down)
    {
        mInput.DOWN = false;
    }
    if(event->key() == Qt::Key_Left)
    {
        mInput.LEFT = false;
    }
    if(event->key() == Qt::Key_Right)
    {
        mInput.RIGHT = false;
    }
    if(event->key() == Qt::Key_U)
    {
    }
    if(event->key() == Qt::Key_O)
    {
    }
}

void RenderWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        mInput.RMB = true;
    if (event->button() == Qt::LeftButton)
        mInput.LMB = true;
    if (event->button() == Qt::MiddleButton)
        mInput.MMB = true;
}

void RenderWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        mInput.RMB = false;
    if (event->button() == Qt::LeftButton)
        mInput.LMB = false;
    if (event->button() == Qt::MiddleButton)
        mInput.MMB = false;
}

void RenderWindow::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    //if RMB, change the speed of the camera
    if (mInput.RMB)
    {
        if (numDegrees.y() < 1)
            setCameraSpeed(0.001f);
        if (numDegrees.y() > 1)
            setCameraSpeed(-0.001f);
    }
    event->accept();
}

void RenderWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mInput.RMB)
    {
        //Using mMouseXYlast as deltaXY so we don't need extra variables
        mMouseXlast = event->pos().x() - mMouseXlast;
        mMouseYlast = event->pos().y() - mMouseYlast;

        if (mMouseXlast != 0)
            mCurrentCamera->yaw(mCameraRotateSpeed * mMouseXlast);
        if (mMouseYlast != 0)
            mCurrentCamera->pitch(mCameraRotateSpeed * mMouseYlast);
    }
    mMouseXlast = event->pos().x();
    mMouseYlast = event->pos().y();
}
// The stuff below this line should be somewhere else in the future.

//Simple way to turn on/off wireframe mode
//Not totally accurate, but draws the objects with
//lines instead of filled polygons
void RenderWindow::toggleWireframe()
{
    mWireframe = !mWireframe;
    if (mWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    //turn on wireframe mode
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);    //turn off wireframe mode
        glEnable(GL_CULL_FACE);
    }
}

//The way this is set up is that we start the clock before doing the draw call,
//and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz
void RenderWindow::calculateFramerate()
{
    long long nsecElapsed = mTimeStart.nsecsElapsed();
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)    //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30) //once pr 30 frames = update the message twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000., 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 60 frames
        }
    }
}

/// Uses QOpenGLDebugLogger if this is present
/// Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << message;
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            qDebug() << "glGetError returns " << err;
        }
    }
}

/// Tries to start the extended OpenGL debugger that comes with Qt
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            qDebug() << "This system can not use QOpenGLDebugLogger, so we revert to glGetError()";

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                qDebug() << "Started OpenGL debug logger!";
        }

        if(mOpenGLDebugLogger)
            mOpenGLDebugLogger->disableMessages(QOpenGLDebugMessage::APISource, QOpenGLDebugMessage::OtherType, QOpenGLDebugMessage::NotificationSeverity);
    }
}

//This function is called from Qt when window is exposed (shown)
//and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact..)
        mRenderTimer->start(1);
        mTimeStart.start();
    }
    mAspectratio = static_cast<float>(width()) / height();
    //    qDebug() << mAspectratio;
    mCurrentCamera->mProjectionMatrix.perspective(45.f, mAspectratio, 1.f, 100.f);
    //    qDebug() << mCamera.mProjectionMatrix;
}

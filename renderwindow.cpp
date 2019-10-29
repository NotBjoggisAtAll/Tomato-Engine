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
#include "Systems/collisionsystem.h"

#include "Managers/entitymanager.h"
#include "Managers/shadermanager.h"
#include "Managers/soundmanager.h"
#include "Components/allcomponents.h"

#include "resourcefactory.h"
#include "world.h"

#include <QJsonDocument>
#include "jsonscene.h"
#include "Systems/scenesystem.h"
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

void RenderWindow::init()
{
    //Connect the gameloop timer to the render function:
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));
    connect(mMainWindow, &MainWindow::spawnObject, this, &RenderWindow::spawnObject);
    connect(mMainWindow, &MainWindow::playGame_signal, this, &RenderWindow::playGame);
    connect(mMainWindow, &MainWindow::stopGame_signal, this, &RenderWindow::stopGame);
    connect(mMainWindow, &MainWindow::createEntity, this, &RenderWindow::createEntity);

    //********************** General OpenGL stuff **********************

    if (!mContext->makeCurrent(this)) {
        qDebug() << "makeCurrent() failed";
        return;
    }
    if (!mInitialized)
        mInitialized = true;

    initializeOpenGLFunctions();

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

    startOpenGLDebugger();

    glEnable(GL_DEPTH_TEST);    //enables depth sorting - must use GL_DEPTH_BUFFER_BIT in glClear
    glEnable(GL_CULL_FACE);     //draws only front side of models - usually what you want -
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //color used in glClear GL_COLOR_BUFFER_BIT

    //**********************  Texture stuff: **********************

    mTexture[0] = new Texture("white.bmp");
    mTexture[1] = new Texture("hund.bmp", 1);
    mTexture[2] = new Texture("skybox.bmp", 2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture[0]->id());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTexture[1]->id());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, mTexture[2]->id());

    //********************** Creating Systems *********************

    world = getWorld();

    resourceFactory = ResourceFactory::get();

    world->registerComponent<Transform>();
    world->registerComponent<Mesh>();
    world->registerComponent<Material>();
    world->registerComponent<Sound>();
    world->registerComponent<EntityData>();
    world->registerComponent<Light>();
    world->registerComponent<Collision>();

    mRenderSystem = world->registerSystem<RenderSystem>();
    mSoundSystem = world->registerSystem<SoundSystem>();
    mMovementSystem = world->registerSystem<MovementSystem>();
    mCollisionSystem = world->registerSystem<CollisionSystem>();
    mSceneSystem = world->registerSystem<SceneSystem>();

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

    Signature collisionSign;
    collisionSign.set(world->getComponentType<Collision>());
    collisionSign.set(world->getComponentType<EntityData>());
    collisionSign.set(world->getComponentType<Transform>());
    world->setSystemSignature<MovementSystem>(collisionSign);

    Signature sceneSign;
    for(const auto& type : world->getComponentTypes())
        sceneSign.set(type.second);


    //********************** Making the objects to be drawn **********************
    jba::JsonScene scene("newScene");

    Entity entity = world->createEntity();

    world->addComponent(entity, EntityData("Sound Source"));
    world->addComponent(entity, Transform());
    world->addComponent(entity, Sound(SoundManager::instance()->createSource("Caravan",{}, "caravan_mono.wav", true, .5f)));

    scene.addObject(entity); // TODO Make soundmanager into a resourcefactory so I can use the same file multiple times without loading it again
    // TODO Fix so the JSON Sound filepath is the actual path and not just the name

    entity = world->createEntity();
    world->addComponent(entity, EntityData("Light Source"));
    world->addComponent(entity, Transform({2.5f, 3.f, 0.f},{},{0.5f,0.5f,0.5f}));
    world->addComponent(entity, Light());
    world->addComponent(entity, Material(ShaderManager::instance()->textureShader(),{1},0));
    world->addComponent(entity, resourceFactory->loadMesh("box2.txt"));

    ShaderManager::instance()->phongShader()->setLight(entity);
    scene.addObject(entity);

    //********************** Set up camera **********************
    mEditorCamera = new Camera(gsl::Vector3D(1.f, 1.f, 4.4f));
    scene.addCamera(mEditorCamera);

    mGameCamera = new Camera(gsl::Vector3D(0));
    scene.addCamera(mGameCamera);

    updateCamera(mEditorCamera);

    //********************** System stuff **********************

    scene.makeFile("default.json", false);
    mSceneSystem->loadScene(fileToLoad_);
    mMainWindow->DisplayEntitesInOutliner();

}

void RenderWindow::render()
{
    handleInput();
    mCurrentCamera->update();

    mTimeStart.restart(); //restart FPS clock
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)

    //to clear the screen for each redraw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    mCollisionSystem->checkCollision();
    mSoundSystem->tick();
    mRenderSystem->tick();


    calculateFramerate();
    mContext->swapBuffers(this);
}

void RenderWindow::recieveJsonPath(QString JsonPath)
{
    fileToLoad_ = JsonPath;
    exposeEvent(nullptr);
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
    world->addComponent(entity, resourceFactory->getCollision(path));

    mMainWindow->addEntityToUi(entity);
}

void RenderWindow::updateCamera(Camera *newCamera)
{
    mCurrentCamera = newCamera;

    //new system - shader sends uniforms so needs to get the view and projection matrixes from camera
    for(auto& Shader : ShaderManager::instance()->mShaders){
        Shader.second->setCurrentCamera(mCurrentCamera);
    }

    getWorld()->setCurrentCamera(newCamera);
}

void RenderWindow::playGame()
{
    updateCamera(mGameCamera);
}

void RenderWindow::stopGame()
{
    updateCamera(mEditorCamera);
}

void RenderWindow::raycastFromMouse(QMouseEvent* event)
{

    float x = (2.0f * event->pos().x()) / width() - 1.0f;
    float y = 1.0f - (2.0f * event->pos().y()) / height();
    float z = 1.0f;
    gsl::Vector3D ray_nds(x, y, z); //nds = normalised device coordinates
    gsl::Vector4D ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f); //clip = Homogeneous Clip Coordinates
    gsl::Matrix4x4 projection_matrix = mCurrentCamera->projectionMatrix_;
    projection_matrix.inverse();
    gsl::Vector4D ray_eye = projection_matrix * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f;
    gsl::Matrix4x4 view_matrix = mCurrentCamera->viewMatrix_;
    view_matrix.inverse();
    gsl::Vector3D ray_world = (view_matrix * ray_eye).toVector3D();
    ray_world.normalize();

    Entity entityPicked = mCollisionSystem->checkMouseCollision(mCurrentCamera->position(),ray_world);

    mMainWindow->updateRightPanel(entityPicked);

    //Move this to another place
    updateCollisionOutline(entityPicked);

}
void RenderWindow::updateCollisionOutline(Entity newEntity){

    if(lastEntityCollision != -1)
    {
        getWorld()->destroyEntity(lastEntityCollision);

        if(newEntity == -1){
            lastEntityCollision = -1;
            return;
        }

    }

    Collision* collision = getWorld()->getComponent<Collision>(newEntity).value_or(nullptr);
    Transform* transform = getWorld()->getComponent<Transform>(newEntity).value_or(nullptr);

    if(!collision || !transform) return;

    gsl::Vector3D min = collision->scaledMinVector_;
    gsl::Vector3D max =  collision->scaledMaxVector_;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    vertices.reserve(8);
    Vertex vertex;
    vertex.set_rgb(1,0,0);

    vertex.set_xyz(min);                    // 0
    vertices.push_back(vertex);
    vertex.set_xyz(max.x, min.y, min.z);    // 1
    vertices.push_back(vertex);
    vertex.set_xyz(max.x, min.y, max.z);    // 2
    vertices.push_back(vertex);
    vertex.set_xyz(min.x, min.y, max.z);    // 3
    vertices.push_back(vertex);
    vertex.set_xyz(min.x, max.y, min.z);    // 4
    vertices.push_back(vertex);
    vertex.set_xyz(max.x, max.y, min.z);    // 5
    vertices.push_back(vertex);
    vertex.set_xyz(max);                    // 6
    vertices.push_back(vertex);
    vertex.set_xyz(min.x, max.y, max.z);    // 7
    vertices.push_back(vertex);

    indices = {
        0,1,
        1,2,
        2,3,
        3,0,
        0,4,
        1,5,
        2,6,
        3,7,
        4,5,
        5,6,
        6,7,
        7,4
    };

    Entity entity = getWorld()->createEntity();

    getWorld()->addComponent(entity, Transform(transform->position_));
    getWorld()->addComponent(entity, resourceFactory->createCollisionbox(vertices,indices));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->colorShader()));
    getWorld()->addComponent(entity, EntityData("Collision"));
    EntityData* data = getWorld()->getComponent<EntityData>(newEntity).value();

    data->children_.push_back(entity);

    lastEntityCollision = entity;

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
    mCurrentCamera->moveForward(0.f);  //cancel last frame movement
    if(mInput.RMB)
    {
        if(mInput.W)
            mCurrentCamera->moveForward(-mCameraSpeed);
        if(mInput.S)
            mCurrentCamera->moveForward(mCameraSpeed);
        if(mInput.D)
            mCurrentCamera->moveRight(mCameraSpeed);
        if(mInput.A)
            mCurrentCamera->moveRight(-mCameraSpeed);
        if(mInput.Q)
            mCurrentCamera->moveUp(-mCameraSpeed);
        if(mInput.E)
            mCurrentCamera->moveUp(mCameraSpeed);
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
    {
        mInput.LMB = true;
        raycastFromMouse(event);
    }
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
            frameCount = 0;     //reset to show a new message in 60
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
    if(fileToLoad_ == "")
        return;

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
    mCurrentCamera->projectionMatrix_.perspective(45.f, mAspectratio, 0.1f, 1000.f);
    mEditorCamera->projectionMatrix_.perspective(45.f, mAspectratio, 0.1f, 1000.f);
    mGameCamera->projectionMatrix_.perspective(45.f, mAspectratio, 0.1f, 1000.f);
    //    qDebug() << mCamera.mProjectionMatrix;
}

Entity RenderWindow::createEntity()
{
    Entity entity = world->createEntity();
    world->addComponent(entity, EntityData("Empty Entity"));
    return entity;
}

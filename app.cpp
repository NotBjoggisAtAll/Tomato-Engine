#include "app.h"
#include "renderwindow.h"
#include "world.h"
#include "Components/allcomponents.h"
#include "resourcefactory.h"
#include "Managers/shadermanager.h"
#include "Managers/soundmanager.h"
#include "Systems/soundsystem.h"
#include "Systems/movementsystem.h"
#include "Systems/collisionsystem.h"
#include "Systems/scriptsystem.h"
#include "Systems/bsplinesystem.h"
#include "Systems/npcsystem.h"
#include "Systems/rendersystem.h"
#include "Systems/scenesystem.h"
#include "Systems/inputsystem.h"
#include "camera.h"
#include "eventhandler.h"
#include "Windows/sceneloader.h"
#include "Windows/scenesaver.h"

App::App()
{
    getWorld()->registerComponent<Transform>();
    getWorld()->registerComponent<Mesh>();
    getWorld()->registerComponent<Material>();
    getWorld()->registerComponent<Sound>();
    getWorld()->registerComponent<EntityData>();
    getWorld()->registerComponent<Light>();
    getWorld()->registerComponent<Collision>();
    getWorld()->registerComponent<Script>();
    getWorld()->registerComponent<BSpline>();
    getWorld()->registerComponent<Npc>();
    getWorld()->registerComponent<Input>();

    getWorld()->registerSystem<SoundSystem>();
    getWorld()->registerSystem<MovementSystem>();
    getWorld()->registerSystem<CollisionSystem>();
    getWorld()->registerSystem<SceneSystem>();
    getWorld()->registerSystem<ScriptSystem>();
    getWorld()->registerSystem<BSplineSystem>();
    getWorld()->registerSystem<RenderSystem>();
    getWorld()->registerSystem<NpcSystem>();
    getWorld()->registerSystem<InputSystem>();

    Signature renderSign;
    renderSign.set(getWorld()->getComponentType<Transform>());
    renderSign.set(getWorld()->getComponentType<Mesh>());
    renderSign.set(getWorld()->getComponentType<Material>());
    getWorld()->setSystemSignature<RenderSystem>(renderSign);

    Signature soundSign;
    soundSign.set(getWorld()->getComponentType<Transform>());
    soundSign.set(getWorld()->getComponentType<Sound>());
    getWorld()->setSystemSignature<SoundSystem>(soundSign);

    Signature movementSign;
    movementSign.set(getWorld()->getComponentType<Transform>());
    movementSign.set(getWorld()->getComponentType<EntityData>());
    movementSign.set(getWorld()->getComponentType<Collision>());
    getWorld()->setSystemSignature<MovementSystem>(movementSign);

    Signature collisionSign;
    collisionSign.set(getWorld()->getComponentType<Collision>());
    collisionSign.set(getWorld()->getComponentType<EntityData>());
    collisionSign.set(getWorld()->getComponentType<Transform>());
    getWorld()->setSystemSignature<CollisionSystem>(collisionSign);

    Signature scriptSign;
    scriptSign.set(getWorld()->getComponentType<Script>());
    getWorld()->setSystemSignature<ScriptSystem>(scriptSign);

    Signature bsplineSign;
    bsplineSign.set(getWorld()->getComponentType<BSpline>());
    bsplineSign.set(getWorld()->getComponentType<Mesh>());
    getWorld()->setSystemSignature<BSplineSystem>(bsplineSign);

    Signature npcSign;
    npcSign.set(getWorld()->getComponentType<Npc>());
    npcSign.set(getWorld()->getComponentType<Transform>());
    getWorld()->setSystemSignature<NpcSystem>(npcSign);

    Signature inputSign;
    inputSign.set(getWorld()->getComponentType<Input>());
    inputSign.set(getWorld()->getComponentType<Transform>());
    getWorld()->setSystemSignature<InputSystem>(inputSign);

    mainWindow_ = std::make_unique<MainWindow>();
    renderWindow_ = mainWindow_->renderWindow_;
    eventHandler_ = std::make_shared<EventHandler>();
    renderWindow_->installEventFilter(eventHandler_.get());
    connect(eventHandler_.get(), &EventHandler::leftMouseButtonPressed, this, &App::raycastFromMouse);

    getWorld()->getSystem<InputSystem>()->setEventHandler(eventHandler_);

    mainWindow_->show();

    //Connect the gameloop timer to the render function:
    connect(&tickTimer_, &QTimer::timeout, this, &App::tick);
    tickTimer_.start(16);
    frameTimer_.start();
    deltaTimer_.start();

    connect(mainWindow_.get(), &MainWindow::spawnObject, this, &App::spawnObject);
    connect(mainWindow_.get(), &MainWindow::playGame_signal, this, &App::playGame);
    connect(mainWindow_.get(), &MainWindow::stopGame_signal, this, &App::stopGame);
    connect(mainWindow_.get(), &MainWindow::createEntity, this, &App::createEntity);
    connect(mainWindow_.get(), &MainWindow::loadScene, this, &App::openSceneLoader);
    connect(mainWindow_.get(), &MainWindow::newScene, this, &App::newScene);
    connect(mainWindow_.get(), &MainWindow::saveScene, this, &App::openSceneSaver);


    connect(renderWindow_.get(), &RenderWindow::updateCameraPerspectives, this, &App::updateCameraPerspectives);
    connect(renderWindow_.get(), &RenderWindow::initDone, this, &App::postInit);

}

App::~App()
{
    SoundManager::instance()->cleanUp();
}
void App::postInit()
{
    Entity entity = getWorld()->createEntity();

    getWorld()->addComponent(entity, EntityData("Sound Source"));
    getWorld()->addComponent(entity, Transform());
    getWorld()->addComponent(entity, Sound(SoundManager::instance()->createSource("Caravan",{}, "caravan_mono.wav", true, .5f)));

    //  scene.addObject(entity); // TODO Make soundmanager into a resourcefactory so I can use the same file multiple times without loading it again
    // TODO Fix so the JSON Sound filepath is the actual path and not just the name

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Light Source"));
    getWorld()->addComponent(entity, Transform({2.5f, 3.f, 0.f},{},{0.5f,0.5f,0.5f}));
    getWorld()->addComponent(entity, Light());
    getWorld()->addComponent(entity, Script("testScript.js"));
    getWorld()->getSystem<ScriptSystem>()->componentAdded(getWorld()->getComponent<Script>(entity).value());

    ShaderManager::instance()->phongShader()->setLight(entity);

    BSpline spline = BSpline(.05f);

    spline.curve_.addControlPoint(gsl::Vector3D(-5,0,-5));
    spline.curve_.addControlPoint(gsl::Vector3D(-2.5,0,2.5));
    spline.curve_.addControlPoint(gsl::Vector3D(0,0,-5));
    spline.curve_.addControlPoint(gsl::Vector3D(2.5,0,2.5));
    spline.curve_.addControlPoint(gsl::Vector3D(5,0,-5));

    entity = getWorld()->createEntity();

    getWorld()->addComponent(entity, spline);
    getWorld()->addComponent(entity, Transform());
    getWorld()->addComponent(entity, ResourceFactory::get()->createLines(spline.curve_.getVerticesAndIndices()));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->colorShader()));
    getWorld()->addComponent(entity, EntityData("BSpline"));


    BSpline* splineptr = getWorld()->getComponent<BSpline>(entity).value_or(nullptr);

    entity = getWorld()->createEntity();

    getWorld()->addComponent(entity, EntityData("Enemy Box"));
    getWorld()->addComponent(entity, Transform({},{},{0.2f,0.2f,0.2f}));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->colorShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("box2.txt"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("box2.txt"));
    getWorld()->addComponent(entity, Npc(&splineptr->curve_));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Player"));
    getWorld()->addComponent(entity, Transform({0,0,1},{},{0.2f,0.2f,0.2f}));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->phongShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("box2.txt"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("box2.txt"));
    getWorld()->addComponent(entity, Input(true));


    mainWindow_->displayEntitiesInOutliner();

    //********************** Set up camera **********************
    editorCamera_ = new Camera(gsl::Vector3D(1.f, 1.f, 4.4f));
    gameCamera_ = new Camera(gsl::Vector3D(0, 12.f, -1));
    gameCamera_->yaw_ = (-180.f);
    gameCamera_->pitch_ = (-90.f);
    getWorld()->setCurrentCamera(editorCamera_);

}


void App::tick()
{
    qDebug() << gameCamera_->position();
    qDebug() << "Yaw: " << gameCamera_->yaw_ << ". Pitch: " << gameCamera_->pitch_;

    deltaTime_ = deltaTimer_.restart() / 1000.f;
    calculateFramerate();

    getWorld()->getSystem<InputSystem>()->tick();

    if(getWorld()->bGameRunning)
    {
        getWorld()->getSystem<ScriptSystem>()->tick();
        getWorld()->getSystem<NpcSystem>()->tick();
    }

    getWorld()->getSystem<BSplineSystem>()->tick();
    getWorld()->getSystem<CollisionSystem>()->tick();
    getWorld()->getSystem<SoundSystem>()->tick();

    getWorld()->getCurrentCamera()->update();
    renderWindow_->tick();
}

Entity App::createEntity()
{
    Entity entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Empty Entity"));
    return entity;
}
Entity App::spawnObject(std::string name, std::string path)
{
    Entity entity = getWorld()->createEntity();
    if(name == "BSpline")
    {
        BSpline spline;
        getWorld()->addComponent(entity, spline);
        getWorld()->addComponent(entity, ResourceFactory::get()->createLines(spline.curve_.getVerticesAndIndices()));
    }
    else
    {
        getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh(path));
    }

    getWorld()->addComponent(entity, EntityData(name));
    getWorld()->addComponent(entity, Transform());
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->colorShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision(path));
    return entity;
}

void App::playGame()
{
    getWorld()->setCurrentCamera(gameCamera_);
    getWorld()->getSystem<SceneSystem>()->beginPlay();
    getWorld()->getSystem<ScriptSystem>()->beginPlay();
}

void App::stopGame()
{
    getWorld()->getSystem<SceneSystem>()->endPlay();
    mainWindow_->displayEntitiesInOutliner();
    getWorld()->setCurrentCamera(editorCamera_);
}

void App::updateCameraPerspectives(float aspectRatio)
{
    editorCamera_->projectionMatrix_.perspective(45.f, aspectRatio, 0.1f, 10000.f);
    gameCamera_->projectionMatrix_.perspective(45.f, aspectRatio, 0.1f, 10000.f);
}
void App::calculateFramerate()
{
    frameCounter++;
    totalDeltaTime_ += deltaTime_;
    double elapsed = frameTimer_.elapsed();
    if(elapsed >= 100)
    {
        mainWindow_->updateStatusbar(totalDeltaTime_/frameCounter, frameCounter/totalDeltaTime_);
        frameCounter = 0;
        totalDeltaTime_ = 0;
        frameTimer_.restart();
    }
}


void App::loadScene(QString JsonPath)
{
    getWorld()->getSystem<SceneSystem>()->loadScene(JsonPath);
    mainWindow_->displayEntitiesInOutliner();
}

void App::openSceneLoader()
{
    SceneLoader* sceneLoader = new SceneLoader(mainWindow_.get());
    sceneLoader->show();
    connect(sceneLoader, &SceneLoader::onLoad, this, &App::loadScene);
}

void App::newScene()
{
    getWorld()->getSystem<SceneSystem>()->clearScene();
}

void App::openSceneSaver()
{
    SceneSaver* sceneSaver_ = new SceneSaver(mainWindow_.get());
    sceneSaver_->show();
    connect(sceneSaver_, &SceneSaver::onSave, this, &App::saveScene);

}

void App::saveScene(QString sceneName)
{
    getWorld()->getSystem<SceneSystem>()->saveScene(sceneName);
}

void App::raycastFromMouse()
{
    auto mousePos = renderWindow_->mapFromGlobal(QCursor::pos());

    float x = (2.0f * mousePos.x()) / renderWindow_->width() - 1.0f;
    float y = 1.0f - (2.0f * mousePos.y()) / renderWindow_->height();
    float z = 1.0f;
    gsl::Vector3D ray_nds(x, y, z); //nds = normalised device coordinates
    gsl::Vector4D ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f); //clip = Homogeneous Clip Coordinates
    gsl::Matrix4x4 projection_matrix = getWorld()->getCurrentCamera()->projectionMatrix_;
    projection_matrix.inverse();
    gsl::Vector4D ray_eye = projection_matrix * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f;
    gsl::Matrix4x4 view_matrix = getWorld()->getCurrentCamera()->viewMatrix_;
    view_matrix.inverse();
    gsl::Vector3D ray_world = (view_matrix * ray_eye).toVector3D();
    ray_world.normalize();

    Entity entityPicked = getWorld()->getSystem<CollisionSystem>()->checkMouseCollision(getWorld()->getCurrentCamera()->position(),ray_world);

    mainWindow_->updateRightPanel(entityPicked);
    renderWindow_->makeCollisionBorder(entityPicked);

}

#include "app.h"
#include "renderwindow.h"
#include "world.h"
#include "Components/allcomponents.h"
#include "Factories/resourcefactory.h"
#include "Factories/guifactory.h"
#include "Factories/texturefactory.h"
#include "Managers/shadermanager.h"
#include "Managers/soundmanager.h"
#include "Systems/allsystems.h"
#include "eventhandler.h"
#include "GSL/gsl_math_extensions.h"
#include <QFileDialog>

App::App()
{
    // Register components
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
    getWorld()->registerComponent<Camera>();
    getWorld()->registerComponent<Projectile>();
    getWorld()->registerComponent<GUI>();

    // Register systems
    getWorld()->registerSystem<SoundSystem>();
    getWorld()->registerSystem<MovementSystem>();
    getWorld()->registerSystem<CollisionSystem>();
    getWorld()->registerSystem<SceneSystem>();
    getWorld()->registerSystem<ScriptSystem>();
    getWorld()->registerSystem<BSplineSystem>();
    getWorld()->registerSystem<RenderSystem>();
    getWorld()->registerSystem<RenderSystem2D>();
    getWorld()->registerSystem<NpcSystem>();
    getWorld()->registerSystem<InputSystem>();
    getWorld()->registerSystem<CameraSystem>();
    getWorld()->registerSystem<ProjectileSystem>();

    // Sets the system signatures
    Signature signature;
    signature.set(getWorld()->getComponentType<Transform>());
    signature.set(getWorld()->getComponentType<Mesh>());
    signature.set(getWorld()->getComponentType<Material>());
    getWorld()->setSystemSignature<RenderSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<GUI>());
    signature.set(getWorld()->getComponentType<Material>());
    getWorld()->setSystemSignature<RenderSystem2D>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Transform>());
    signature.set(getWorld()->getComponentType<Sound>());
    getWorld()->setSystemSignature<SoundSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Transform>());
    signature.set(getWorld()->getComponentType<EntityData>());
    signature.set(getWorld()->getComponentType<Collision>());
    getWorld()->setSystemSignature<MovementSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Collision>());
    signature.set(getWorld()->getComponentType<Transform>());
    getWorld()->setSystemSignature<CollisionSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Script>());
    getWorld()->setSystemSignature<ScriptSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<BSpline>());
    signature.set(getWorld()->getComponentType<Mesh>());
    getWorld()->setSystemSignature<BSplineSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Npc>());
    signature.set(getWorld()->getComponentType<Transform>());
    getWorld()->setSystemSignature<NpcSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Input>());
    signature.set(getWorld()->getComponentType<Transform>());
    getWorld()->setSystemSignature<InputSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Transform>());
    signature.set(getWorld()->getComponentType<Camera>());
    getWorld()->setSystemSignature<CameraSystem>(signature);

    signature.reset();
    signature.set(getWorld()->getComponentType<Projectile>());
    signature.set(getWorld()->getComponentType<Transform>());
    getWorld()->setSystemSignature<ProjectileSystem>(signature);


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
    connect(mainWindow_.get(), &MainWindow::loadScene, this, &App::loadScene);
    connect(mainWindow_.get(), &MainWindow::newScene, this, &App::newScene);
    connect(mainWindow_.get(), &MainWindow::saveScene, this, &App::saveScene);

    connect(renderWindow_.get(), &RenderWindow::updateCameraPerspectives, this, &App::updateCameraPerspectives);
    connect(getWorld(), &World::updateCameraPerspectives, renderWindow_.get(), &RenderWindow::callExposeEvent);
    connect(getWorld(), &World::updateWorldOutliner, this, &App::updateWorldOutliner);
    connect(renderWindow_.get(), &RenderWindow::initDone, this, &App::postInit);

    connect(getWorld()->getSystem<CollisionSystem>().get(), &CollisionSystem::entitiesCollided, this, &App::entitiesCollided);
}

App::~App()
{
    SoundManager::instance()->cleanUp();
}

void App::postInit()
{
    Entity entity = getWorld()->createEntity();

    Camera camera;
    camera.isInUse_ = true;
    camera.isEditor = true;

    getWorld()->addComponent(entity, camera);
    getWorld()->addComponent(entity, Transform(gsl::Vector3D(1.f, 1.f, 4.4f)));
    getWorld()->setCurrentCamera(entity);

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, Transform({0,0,0},{},{}));
    getWorld()->addComponent(entity, Material(ShaderManager::get()->plainShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("axis"));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Sound Source"));
    getWorld()->addComponent(entity, Transform());
    getWorld()->addComponent(entity, Sound(SoundManager::instance()->createSource("Caravan", "shoot_1.wav", true, .5f)));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Light Source"));
    getWorld()->addComponent(entity, Transform({2.5f, 3.f, 0.f},{},{0.5f,0.5f,0.5f}));
    getWorld()->addComponent(entity, Light());

    ShaderManager::get()->phongShader()->setLight(entity);

    BSpline spline = BSpline(.05f);

    spline.curve_.addControlPoint(gsl::Vector3D(-5,0,5));
    spline.curve_.addControlPoint(gsl::Vector3D(5,0,5));
    spline.curve_.addControlPoint(gsl::Vector3D(5,0,3));
    spline.curve_.addControlPoint(gsl::Vector3D(-5,0,1));
    spline.curve_.addControlPoint(gsl::Vector3D(5,0,1));
    spline.curve_.addControlPoint(gsl::Vector3D(5,0,-1));
    spline.curve_.addControlPoint(gsl::Vector3D(0,0,-1));
    spline.curve_.addControlPoint(gsl::Vector3D(5,0,-3));
    spline.curve_.addControlPoint(gsl::Vector3D(-5,0,-5));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("BSpline"));
    getWorld()->addComponent(entity, spline);
    getWorld()->addComponent(entity, Transform());
    getWorld()->addComponent(entity, ResourceFactory::get()->createLines(spline.curve_.getVerticesAndIndices()));
    getWorld()->addComponent(entity, Material(ShaderManager::get()->plainShader()));
    getWorld()->addComponent(entity, Script("enemyManager.js"));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("UI Test"));
    getWorld()->addComponent(entity, Material(ShaderManager::get()->guiShader(),{1,0,0},"hund.bmp"));
    getWorld()->addComponent(entity, GUIFactory::get()->createGUI({0.5,0},{0.1f,0.1f}));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Floor"));
    getWorld()->addComponent(entity, Transform({0,0,0},{},{5,5,5}));
    getWorld()->addComponent(entity, Material(ShaderManager::get()->textureShader(),"ground_path.bmp"));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("plane"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("plane"));
    Mesh* mesh = getWorld()->getComponent<Mesh>(entity).value();
    mesh->isAffectedByFrustum_ = false;

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Game Camera"));
    getWorld()->addComponent(entity, Transform(gsl::Vector3D(0,13,0)));
    getWorld()->addComponent(entity, Camera(false, -180.f,-90.f));
    getWorld()->addComponent(entity, Material(ShaderManager::get()->plainShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCameraFrustum());


    mainWindow_->displayEntitiesInOutliner();

}

void App::tick()
{
    deltaTime_ = deltaTimer_.restart() / 1000.f;
    calculateFramerate();

    getWorld()->getSystem<InputSystem>()->tick(deltaTime_);

    if(getWorld()->bGameRunning)
    {
        getWorld()->getSystem<NpcSystem>()->tick(deltaTime_);
        getWorld()->getSystem<ScriptSystem>()->tick(deltaTime_);
    }

    getWorld()->getSystem<BSplineSystem>()->tick(deltaTime_);
    getWorld()->getSystem<ProjectileSystem>()->tick(deltaTime_);
    getWorld()->getSystem<SoundSystem>()->tick(deltaTime_);
    getWorld()->getSystem<CollisionSystem>()->tick(deltaTime_);

    getWorld()->getSystem<CameraSystem>()->tick(deltaTime_);
    renderWindow_->tick(deltaTime_);
    getWorld()->destroyEntities();
}

void App::entitiesCollided(Entity entity1, Entity entity2)
{
    Projectile* projectile = getWorld()->getComponent<Projectile>(entity1).value_or(nullptr);
    if(projectile)
    {
        Npc* npc = getWorld()->getComponent<Npc>(entity2).value_or(nullptr);
        if(npc)
        {
            getWorld()->destroyEntityLater(entity1);
            getWorld()->destroyEntityLater(entity2);
        }
    }
}

void App::spawnTower(gsl::Vector3D hitPosition)
{
    Transform transform;
    transform.position_ = hitPosition + gsl::Vector3D(0,0.1f,0);
    transform.scale_ = gsl::Vector3D(0.2f,0.2f,0.2f);
    Entity entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, transform);
    getWorld()->addComponent(entity, EntityData("Tower"));
    getWorld()->addComponent(entity, Material(ShaderManager::get()->phongShader(),gsl::Vector3D(0.82f,0.82f,0.82f)));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("turret.obj"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("turret.obj"));
    getWorld()->addComponent(entity, Script("towerScript.js"));
    auto script = getWorld()->getComponent<Script>(entity).value();
    getWorld()->getSystem<ScriptSystem>()->componentAdded(script, entity);
    mainWindow_->addEntityToUi(entity);

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
    getWorld()->addComponent(entity, Material(ShaderManager::get()->plainShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision(path));
    mainWindow_->addEntityToUi(entity);
    return entity;
}

void App::playGame()
{
    getWorld()->getSystem<SceneSystem>()->beginPlay();
    getWorld()->getSystem<SoundSystem>()->beginPlay();
    getWorld()->getSystem<ScriptSystem>()->beginPlay();
}

void App::stopGame()
{
    getWorld()->getSystem<SoundSystem>()->endPlay();
    getWorld()->getSystem<NpcSystem>()->endPlay();
    getWorld()->getSystem<ScriptSystem>()->endPlay();
    getWorld()->getSystem<SceneSystem>()->endPlay();
    mainWindow_->displayEntitiesInOutliner();
}

void App::updateCameraPerspectives(float aspectRatio)
{
    float fov = 45.f;
    for(const auto& entity : getWorld()->getSystem<CameraSystem>()->entities_)
    {
        Camera* camera = getWorld()->getComponent<Camera>(entity).value_or(nullptr);
        camera->aspectRatio_ = aspectRatio;
        camera->fieldOfView_ = fov;
        camera->projectionMatrix_.perspective(fov, aspectRatio, 0.1f, 10000.f);
    }
}
void App::calculateFramerate()
{
    frameCounter++;
    totalDeltaTime_ += deltaTime_;
    double elapsed = frameTimer_.elapsed();
    if(elapsed >= 100)
    {
        mainWindow_->updateStatusbar(totalDeltaTime_/frameCounter, frameCounter/totalDeltaTime_, getWorld()->getSystem<RenderSystem>()->totalVerticeCount);
        frameCounter = 0;
        totalDeltaTime_ = 0;
        frameTimer_.restart();
    }
}

void App::loadScene()
{
    QFileDialog fileDialog;
    QFileInfo fileInfo = fileDialog.getOpenFileName(mainWindow_.get(),"Pick a scene","../INNgine2019/Json","*.json");

    if(!fileInfo.size())
        return;

    getWorld()->getSystem<SceneSystem>()->loadScene(fileInfo);
    updateWorldOutliner();
}

void App::newScene()
{
    getWorld()->getSystem<SceneSystem>()->clearScene();
}

void App::updateWorldOutliner()
{
    mainWindow_->displayEntitiesInOutliner();
}

void App::saveScene()
{
    QString file = QFileDialog::getSaveFileName(mainWindow_.get(),"Save a scene","../INNgine2019/Json/newScene", "*.json");

    if(!file.size())
        return;

    QFileInfo fileInfo(file);
    getWorld()->getSystem<SceneSystem>()->saveScene(fileInfo);
}

void App::raycastFromMouse()
{
    QPoint mousePos = renderWindow_->mapFromGlobal(QCursor::pos());

    gsl::Vector2D mousePosVector2D = gsl::Vector2D(mousePos.x(), mousePos.y());
    gsl::Vector2D screenWidthHeight = gsl::Vector2D(renderWindow_->width(), renderWindow_->height());

    HitResult hit;
    HitResult2D hit2D;

    if(getWorld()->getSystem<CollisionSystem>()->checkMouseCollision2D(mousePosVector2D,screenWidthHeight,hit2D))
    {
        //Button press here.


        if(!getWorld()->bGameRunning)
        {
            renderWindow_->makeCollisionBorder(hit2D.entityHit);
            mainWindow_->updateRightPanel(hit2D.entityHit);
        }
        return;
    }
    // No UI elements hit. Testing for 3D Objects
    else if(getWorld()->getSystem<CollisionSystem>()->checkMouseCollision(mousePosVector2D,screenWidthHeight,hit))
    {
        if(getWorld()->bGameRunning)
        {
            EntityData* data = getWorld()->getComponent<EntityData>(hit.entityHit).value_or(nullptr);
            if(data)
            {
                if(data->name_ == "Floor")
                    spawnTower(hit.position);
            }
        }
        else
        {
            renderWindow_->makeCollisionBorder(hit.entityHit);
            mainWindow_->updateRightPanel(hit.entityHit);
        }
    }
    else
    {
        renderWindow_->makeCollisionBorder(-1);
        mainWindow_->updateRightPanel(-1);
    }
}

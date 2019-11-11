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
#include "Systems/camerasystem.h"
#include "eventhandler.h"
#include "Systems/scenesystem.h"
#include "Systems/inputsystem.h"
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
    getWorld()->registerComponent<VertexData>();
    getWorld()->registerComponent<Destructable>();
    getWorld()->registerComponent<Camera>();

    getWorld()->registerSystem<SoundSystem>();
    getWorld()->registerSystem<MovementSystem>();
    getWorld()->registerSystem<CollisionSystem>();
    getWorld()->registerSystem<SceneSystem>();
    getWorld()->registerSystem<ScriptSystem>();
    getWorld()->registerSystem<BSplineSystem>();
    getWorld()->registerSystem<RenderSystem>();
    getWorld()->registerSystem<NpcSystem>();
    getWorld()->registerSystem<InputSystem>();
    getWorld()->registerSystem<CameraSystem>();

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

    Signature cameraSign;
    cameraSign.set(getWorld()->getComponentType<Transform>());
    cameraSign.set(getWorld()->getComponentType<Camera>());
    getWorld()->setSystemSignature<CameraSystem>(cameraSign);

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
    connect(getWorld(), &World::updateCameraPerspectives, renderWindow_.get(), &RenderWindow::callExposeEvent);
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

    //    getWorld()->addComponent(entity, EntityData("Sound Source"));
    //    getWorld()->addComponent(entity, Transform());
    //    getWorld()->addComponent(entity, Sound(SoundManager::instance()->createSource("Caravan",{}, "caravan_mono.wav", true, .5f)));

    //    //  scene.addObject(entity); // TODO Make soundmanager into a resourcefactory so I can use the same file multiple times without loading it again
    //    // TODO Fix so the JSON Sound filepath is the actual path and not just the name

    //    entity = getWorld()->createEntity();

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Light Source"));
    getWorld()->addComponent(entity, Transform({2.5f, 3.f, 0.f},{},{0.5f,0.5f,0.5f}));
    getWorld()->addComponent(entity, Light());

    ShaderManager::instance()->phongShader()->setLight(entity);

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

    getWorld()->addComponent(entity, spline);
    getWorld()->addComponent(entity, Transform());
    getWorld()->addComponent(entity, ResourceFactory::get()->createLines(spline.curve_.getVerticesAndIndices()));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->plainShader()));
    getWorld()->addComponent(entity, EntityData("BSpline"));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Floor"));
    getWorld()->addComponent(entity, Transform({-5,0,-5},{},{10,10,10}));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->colorShader(),{.2f,.7f,.1f}));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("plane"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("plane"));


    entity = getWorld()->createEntity();

    getWorld()->addComponent(entity, EntityData("Enemy"));
    getWorld()->addComponent(entity, Transform({},{},{0.2f,0.2f,0.2f}));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->phongShader(),{.2f,.7f,.1f}));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("box2.txt"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("box2.txt"));

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Player"));
    getWorld()->addComponent(entity, Transform({0,0,1},{},{0.2f,0.2f,0.2f}));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->phongShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("box2.txt"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("box2.txt"));
    getWorld()->addComponent(entity, Input(true));

    entity = getWorld()->createEntity();

    entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, EntityData("Game Camera"));
    getWorld()->addComponent(entity, Camera(false, -180.f,-90.f));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->plainShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCameraFrustum());
    getWorld()->addComponent(entity, Transform(gsl::Vector3D(0,13,0)));

    mainWindow_->displayEntitiesInOutliner();

}

void App::entitiesCollided(Entity entity1, Entity entity2)
{
    Input* player = getWorld()->getComponent<Input>(entity1).value_or(nullptr);
    if(player)
    {
        Destructable* item = getWorld()->getComponent<Destructable>(entity2).value_or(nullptr);
        if(item)
        {
            Transform* data = getWorld()->getComponent<Transform>(entity2).value_or(nullptr);
            gsl::Vector3D pos = data->position_;
            getWorld()->destroyEntity(entity2);
            for(const auto& entity : getWorld()->getSystem<NpcSystem>()->entities_)
            {
                Npc* npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
                npc->event = NPCevents::ITEM_TAKEN;
                getWorld()->getSystem<NpcSystem>()->notify(entity, pos);
            }
        }
        Npc* npc = getWorld()->getComponent<Npc>(entity2).value_or(nullptr);
        if(npc)
        {
            getWorld()->destroyEntity(entity1);
        }
    }
}

void App::tick()
{

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

    getWorld()->getSystem<CameraSystem>()->tick();
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
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->plainShader()));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision(path));
    mainWindow_->addEntityToUi(entity);
    return entity;
}

void App::playGame()
{
    setupVisimOblig();
    getWorld()->getSystem<SceneSystem>()->beginPlay();
    getWorld()->getSystem<ScriptSystem>()->beginPlay();

}

void App::stopGame()
{
    getWorld()->getSystem<NpcSystem>()->endPlay();
    getWorld()->getSystem<SceneSystem>()->endPlay();
    mainWindow_->displayEntitiesInOutliner();

    setupVisimOblig();
}

void App::setupVisimOblig()
{
    Entity bsplineID = -1;
    Entity npcID = -1;
    Entity terrainID = -1;
    Entity playerID = -1;

    std::vector<Entity> itemsIDs;

    for(auto entity : getWorld()->getEntities())
    {
        EntityData* entityData = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);
        if(entityData)
        {
            if(entityData->name_ == "Item")
                itemsIDs.push_back(entity);
        }

        BSpline* bspline = getWorld()->getComponent<BSpline>(entity).value_or(nullptr);
        if(bspline)
            bsplineID = entity;

        Npc* npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
        if(npc)
            npcID = entity;

        VertexData* terrain = getWorld()->getComponent<VertexData>(entity).value_or(nullptr);
        if(terrain)
            terrainID = entity;

        Input* input = getWorld()->getComponent<Input>(entity).value_or(nullptr);
        if(input)
            playerID = entity;
    }
    if(bsplineID == -1 || npcID == -1 || terrainID == -1 || playerID == -1) return;


    Npc* npc = getWorld()->getComponent<Npc>(npcID).value_or(nullptr);
    BSpline* bspline = getWorld()->getComponent<BSpline>(bsplineID).value_or(nullptr);

    npc->terrainId = terrainID;
    npc->bSplineCurve = &bspline->curve_;

    getWorld()->getSystem<InputSystem>()->setTerrainId(terrainID);

    for(auto entity : itemsIDs)
    {
        Transform* transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        if(!transform) return;
        transform->position_.y = getWorld()->getSystem<InputSystem>()->getHeightBaryc(entity, terrainID);
    }
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

    auto camera = getWorld()->getComponent<Camera>(getWorld()->getCurrentCamera()).value_or(nullptr);
    auto transform = getWorld()->getComponent<Transform>(getWorld()->getCurrentCamera()).value_or(nullptr);

    float x = (2.0f * mousePos.x()) / renderWindow_->width() - 1.0f;
    float y = 1.0f - (2.0f * mousePos.y()) / renderWindow_->height();
    float z = 1.0f;
    gsl::Vector3D ray_nds(x, y, z); //nds = normalised device coordinates
    gsl::Vector4D ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f); //clip = Homogeneous Clip Coordinates
    gsl::Matrix4x4 projection_matrix = camera->projectionMatrix_;
    projection_matrix.inverse();
    gsl::Vector4D ray_eye = projection_matrix * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f;
    gsl::Matrix4x4 view_matrix = camera->viewMatrix_;
    view_matrix.inverse();
    gsl::Vector3D ray_world = (view_matrix * ray_eye).toVector3D();
    ray_world.normalize();

    Entity entityPicked = getWorld()->getSystem<CollisionSystem>()->checkMouseCollision(transform->position_,ray_world);

    mainWindow_->updateRightPanel(entityPicked);
    renderWindow_->makeCollisionBorder(entityPicked);

}

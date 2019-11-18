#include "scenesystem.h"
#include "world.h"
#include "types.h"
#include <QJsonArray>
#include "Components/allcomponents.h"
#include <QFile>
#include <QJsonDocument>
#include "Managers/shadermanager.h"
#include "phongshader.h"
#include "constants.h"
#include "jsonscene.h"
#include "resourcefactory.h"

SceneSystem::SceneSystem() {}

void SceneSystem::clearScene()
{
    auto tempEntities = entities_;
    auto currentCameraIterator = tempEntities.find(getWorld()->getCurrentCamera());
    if(currentCameraIterator != tempEntities.end())
    {
        Camera* camera = getWorld()->getComponent<Camera>(*currentCameraIterator).value_or(nullptr);
        if(camera)
        {
            if(camera->isEditor)
                tempEntities.erase(currentCameraIterator);
        }
    }
    for(auto entity : tempEntities)
        getWorld()->destroyEntityLater(entity);

}

void SceneSystem::beginPlay()
{
    editorCamera_.camera_    = *getWorld()->getComponent<Camera>(getWorld()->getCurrentCamera()).value();
    editorCamera_.transform_ = *getWorld()->getComponent<Transform>(getWorld()->getCurrentCamera()).value();

    getWorld()->destroyEntityLater(getWorld()->getCurrentCamera());

    jba::JsonScene scene("temp");
    for(auto entity : entities_)
        scene.addObject(entity);
    scene.makeTempFile("temp");

    //Leter etter første kamera blant entites som ikke er et editor kamera og setter denne til current kamera.
    for(const auto& entity : entities_)
    {
        auto camera = getWorld()->getComponent<Camera>(entity).value_or(nullptr);
        if(camera)
        {
            if(camera->isEditor == false)
            {
                camera->isInUse_ = true;
                getWorld()->setCurrentCamera(entity);
                camera->right_ = gsl::Vector3D(1.f, 0.f, 0.f);
                camera->right_.rotateY(camera->yaw_);
                camera->right_.normalize();
                camera->up_ = gsl::Vector3D(0.f, 1.f, 0.f);
                camera->up_.rotateX(camera->pitch_);
                camera->up_.normalize();
                camera->forward_ = camera->up_^camera->right_;

                camera->right_ = camera->forward_^camera->up_;
                camera->right_.normalize();
                return;
            }
        }
    }
}

void SceneSystem::tick(float deltaTime)
{
}

void SceneSystem::endPlay()
{
    loadScenePriv("temp.json");

    //Resets to the editor camera
    Entity entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, editorCamera_.camera_);
    getWorld()->addComponent(entity, editorCamera_.transform_);
    getWorld()->setCurrentCamera(entity);

}

void SceneSystem::loadScene(QFileInfo scene)
{
    editorCamera_.camera_    = *getWorld()->getComponent<Camera>(getWorld()->getCurrentCamera()).value();
    editorCamera_.transform_ = *getWorld()->getComponent<Transform>(getWorld()->getCurrentCamera()).value();
    loadScenePriv(scene.filePath());
    //Resets to the editor camera
    Entity entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, editorCamera_.camera_);
    getWorld()->addComponent(entity, editorCamera_.transform_);
    getWorld()->setCurrentCamera(entity);}

void SceneSystem::saveScene(QFileInfo scene)
{
    jba::JsonScene jscene(scene.baseName());
    for(auto entity : entities_)
        jscene.addObject(entity);

    jscene.makeFile(scene.filePath(),true);
}

void SceneSystem::loadScenePriv(QString sceneName)
{

    clearScene();

    QFile file(sceneName);
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject JSON = doc.object();

    std::unordered_map<std::string, ComponentType> ComponentTypes = getWorld()->getComponentTypes();

    QJsonValue entities = JSON.take("entities");
    if(entities != QJsonValue::Undefined)
    {

        //Array of Entities
        QJsonArray entitiesArray = entities.toArray();

        for(const auto entity : entitiesArray)
        {
            QJsonObject JSONentity = entity.toObject();

            Entity newEntity = getWorld()->createEntity();

            //Current Entity Object Should loop from here
            QJsonObject components = JSONentity.take("components").toObject();


            QJsonObject entityData = components.take("entitydata").toObject();
            if(!entityData.empty())
                getWorld()->addComponent(newEntity,EntityData(entityData));

            //Try to get the material component from JSON
            QJsonObject materialData = components.take("material").toObject();
            //If its not there the entity doesnt have one
            if(!materialData.empty())
                getWorld()->addComponent(newEntity,Material(materialData));

            QJsonObject transformData = components.take("transform").toObject();
            if(!transformData.empty())
                getWorld()->addComponent(newEntity,Transform(transformData));

            QJsonObject meshData = components.take("mesh").toObject();
            if(!meshData.empty())
            {
                getWorld()->addComponent(newEntity,Mesh(meshData));
                if(meshData["filepath"].toString().toStdString().find(".terrain") != std::string::npos)
                {
                    getWorld()->addComponent(newEntity, ResourceFactory::get()->getLastTerrainImported());
                }
            }

            QJsonObject collisionData = components.take("collision").toObject();
            if(!collisionData.empty())
                getWorld()->addComponent(newEntity,Collision(collisionData));

            QJsonObject lightData = components.take("light").toObject();
            if(!lightData.empty())
            {
                getWorld()->addComponent(newEntity,Light(lightData));
                ShaderManager::instance()->phongShader()->setLight(newEntity);
            }
            QJsonObject soundData = components.take("sound").toObject();
            if(!soundData.empty())
                getWorld()->addComponent(newEntity,Sound(soundData));

            QJsonObject scriptData = components.take("script").toObject();
            if(!scriptData.empty())
                getWorld()->addComponent(newEntity,Script(scriptData));

            QJsonObject bsplineData = components.take("bspline").toObject();
            if(!bsplineData.empty())
            {
                BSpline spline;
                spline.fromJson(bsplineData);
                getWorld()->addComponent(newEntity,spline);
            }
            QJsonObject npcData = components.take("npc").toObject();
            if(!npcData.empty())
            {
                Npc npc;
                npc.fromJson(npcData);
                getWorld()->addComponent(newEntity,npc);
            }
            QJsonObject inputData = components.take("input").toObject();
            if(!inputData.empty())
                getWorld()->addComponent(newEntity, Input(inputData));

            QJsonObject destData = components.take("destructable").toObject();
            if(!destData.empty())
                getWorld()->addComponent(newEntity, Destructable(destData));

            QJsonObject cameraData = components.take("camera").toObject();
            if(!cameraData.empty())
            {
                getWorld()->addComponent(newEntity, Camera(cameraData));
            }
        }
    }
}

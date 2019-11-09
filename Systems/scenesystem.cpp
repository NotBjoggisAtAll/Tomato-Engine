#include "scenesystem.h"
#include "world.h"
#include "types.h"
#include <QJsonArray>
#include "Components/allcomponents.h"
#include <QFile>
#include "cameraclass.h"
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
    for(auto entity : tempEntities)
        getWorld()->destroyEntity(entity);

}

void SceneSystem::beginPlay()
{
    jba::JsonScene scene("temp");
    for(auto entity : entities_)
        scene.addObject(entity);
    scene.makeTempFile("temp");
}

void SceneSystem::tick()
{
}

void SceneSystem::endPlay()
{
    loadScenePriv("temp.json");
}

void SceneSystem::loadScene(QString sceneName)
{
    loadScenePriv(QString::fromStdString(gsl::jsonFilePath) + sceneName + ".json");
}

void SceneSystem::saveScene(QString sceneName)
{
    jba::JsonScene scene(sceneName);
    for(auto entity : entities_)
        scene.addObject(entity);

    scene.makeFile(sceneName,true);
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
                getWorld()->setCurrentCamera(newEntity);
            }

        }
    }
}

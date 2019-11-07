#include "scenesystem.h"
#include "world.h"
#include "types.h"
#include <QJsonArray>
#include "Components/allcomponents.h"
#include <QFile>
#include "camera.h"
#include <QJsonDocument>
#include "Managers/shadermanager.h"
#include "phongshader.h"
#include "constants.h"
#include "jsonscene.h"

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
    clearScene();

    currentScene_ = "temp";

    QFile file("temp.json");
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject JSON = doc.object();

    std::unordered_map<std::string, ComponentType> ComponentTypes = getWorld()->getComponentTypes();

    QJsonObject camera = JSON.take("camera").toObject();
    getWorld()->getCurrentCamera()->fromJson(camera);

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
                getWorld()->addComponent(newEntity,Mesh(meshData));

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
        }
    }
}

void SceneSystem::loadScene(QString sceneName)
{
    clearScene();

    currentScene_ = sceneName;

    QFile file(QString::fromStdString(gsl::jsonFilePath) + sceneName + ".json");
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject JSON = doc.object();

    std::unordered_map<std::string, ComponentType> ComponentTypes = getWorld()->getComponentTypes();

    QJsonObject camera = JSON.take("camera").toObject();
    getWorld()->getCurrentCamera()->fromJson(camera);

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
                getWorld()->addComponent(newEntity,Mesh(meshData));

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
        }
    }
}

void SceneSystem::saveScene(QString sceneName)
{
    jba::JsonScene scene(sceneName);
    for(auto entity : entities_)
        scene.addObject(entity);

    scene.makeFile(sceneName,true);
}

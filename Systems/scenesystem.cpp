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
void SceneSystem::clearScene()
{
    auto lol = mEntities;
    for(auto entity : lol)
        getWorld()->destroyEntity(entity);

}

void SceneSystem::loadScene(QString filepath)
{
    clearScene();

    QFile file(QString::fromStdString(gsl::jsonFilePath) + filepath);
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject JSON = doc.object();


    std::unordered_map<std::string, ComponentType> ComponentTypes = getWorld()->getComponentTypes();

    QJsonArray camera = JSON.take("cameras").toArray();
    if(!camera.empty())
    {
        getWorld()->setCurrentCamera(new Camera(camera.takeAt(0).toObject()));
    }

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

        }
    }
}

SceneSystem::SceneSystem()
{

}

#include "scenesystem.h"
#include "World.h"
#include "types.h"
#include <QJsonArray>
#include <cassert>
#include "Components/allcomponents.h"
#include <QFile>
void SceneSystem::clearScene()
{

}

void SceneSystem::loadScene(QString filepath)
{
    //   clearScene();

    QFile file(filepath);
    file.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject JSON = doc.object();


    std::unordered_map<std::string, ComponentType> ComponentTypes = getWorld()->getComponentTypes();

    QJsonValue entities = JSON.take("entities");
    if(entities != QJsonValue::Undefined)
    {

        Entity newEntity = getWorld()->createEntity();

        //Array of Entities
        QJsonArray entitiesArray = entities.toArray();

        //Current Entity Object Should loop from here
        QJsonObject JSONentity = entitiesArray.first().toObject();
        entitiesArray.removeFirst();

        QJsonObject components = JSONentity.take("components").toObject();

        QJsonObject entityData = components.take("entitydata").toObject();

        if(!entityData.empty())
        {
            EntityData data(entityData);
            getWorld()->addComponent(newEntity,data);
        }
        //Try to get the material component from JSON
        QJsonObject materialData = components.take("material").toObject();

        //If its not there the entity doesnt have one
        if(!materialData.empty())
        {
            Material material(materialData);
            getWorld()->addComponent(newEntity,material);

        }

        QJsonObject transformData = components.take("transform").toObject();

        if(!transformData.empty())
        {
            Transform transform(transformData);
            getWorld()->addComponent(newEntity,transform);
        }

        QJsonObject meshData = components.take("mesh").toObject();
        if(!meshData.empty())
        {
            Mesh mesh(meshData);
            getWorld()->addComponent(newEntity,mesh);
        }
    }


}

SceneSystem::SceneSystem()
{

}

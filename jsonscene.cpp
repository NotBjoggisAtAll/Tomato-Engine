#include "jsonscene.h"
#include <QFile>
#include <QJsonDocument>
#include "World.h"
#include "Components/allcomponents.h"
#include "camera.h"
namespace jba {


JsonScene::JsonScene(QString SceneName)
{
    sceneObject_.insert("scene", SceneName);
}

void JsonScene::makeFile(QString FilePath, bool overwrite)
{
    QFile file(FilePath);
    if(file.exists() && !overwrite)
        return;
    else
        file.remove();


    QJsonDocument doc;
    sceneObject_.insert("entities", entities_);
    sceneObject_.insert("cameras", cameras_);

    doc.setObject(sceneObject_);


    file.open(QFile::WriteOnly);
    file.write(doc.toJson());
    file.close();

}

void JsonScene::addObject(Entity entity)
{
    QJsonObject entityObject;
    QJsonObject components;

    EntityData* data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);
    if(data)
        components.insert("entitydata", data->toJSON());

    Transform* transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if(transform)
        components.insert("transform", transform->toJSON());

    Material* material = getWorld()->getComponent<Material>(entity).value_or(nullptr);
    if(material)
        components.insert("material", material->toJSON());

    Mesh* mesh = getWorld()->getComponent<Mesh>(entity).value_or(nullptr);
    if(mesh)
        components.insert("mesh", mesh->toJSON());

    Collision* collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
    if(collision)
        components.insert("collision", collision->toJSON());

    Light* light = getWorld()->getComponent<Light>(entity).value_or(nullptr);
    if(light)
        components.insert("light", light->toJSON());

    Sound* sound = getWorld()->getComponent<Sound>(entity).value_or(nullptr);
    if(sound)
        components.insert("sound", sound->toJSON());

    // Legg til flere komponenter her etterhvert
    entityObject.insert("id", entity);
    entityObject.insert("components", components);

    entities_.push_back(entityObject);

}

void JsonScene::addCamera(Camera* Camera)
{
    QJsonObject object = Camera->toJson();
    cameras_.push_back(object);
}
}

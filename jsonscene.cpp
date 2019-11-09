#include "jsonscene.h"
#include <QFile>
#include <QJsonDocument>
#include "world.h"
#include "Components/allcomponents.h"
#include "cameraclass.h"
#include "constants.h"

namespace jba {

JsonScene::JsonScene(QString SceneName)
{
    sceneObject_.insert("scene", SceneName);
}

void JsonScene::makeTempFile(QString sceneName)
{
    QFile file(sceneName + ".json");
    if(file.exists())
        file.remove();

    QJsonDocument doc;
    sceneObject_.insert("entities", entities_);

    doc.setObject(sceneObject_);


    file.open(QFile::WriteOnly);
    file.write(doc.toJson());
    file.close();
}

void JsonScene::makeFile(QString sceneName, bool overwrite)
{
    QFile file(QString::fromStdString(gsl::jsonFilePath) + sceneName + ".json");
    if(file.exists() && !overwrite)
        return;
    else
        file.remove();


    QJsonDocument doc;
    sceneObject_.insert("entities", entities_);

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
    {
        if(data->name_ == "__collision") return;
        components.insert("entitydata", data->toJson());
    }

    Transform* transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if(transform)
        components.insert("transform", transform->toJson());

    Material* material = getWorld()->getComponent<Material>(entity).value_or(nullptr);
    if(material)
        components.insert("material", material->toJson());

    Mesh* mesh = getWorld()->getComponent<Mesh>(entity).value_or(nullptr);
    if(mesh)
        components.insert("mesh", mesh->toJson());

    Collision* collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
    if(collision)
        components.insert("collision", collision->toJson());

    Light* light = getWorld()->getComponent<Light>(entity).value_or(nullptr);
    if(light)
        components.insert("light", light->toJson());

    Sound* sound = getWorld()->getComponent<Sound>(entity).value_or(nullptr);
    if(sound)
        components.insert("sound", sound->toJson());

    Script* script = getWorld()->getComponent<Script>(entity).value_or(nullptr);
    if(script)
        components.insert("script", script->toJson());

    BSpline* bspline = getWorld()->getComponent<BSpline>(entity).value_or(nullptr);
    if(bspline)
        components.insert("bspline", bspline->toJson());

    Npc* npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
    if(npc)
        components.insert("npc", npc->toJson());

    Input* input = getWorld()->getComponent<Input>(entity).value_or(nullptr);
    if(input)
        components.insert("input", input->toJson());

    Destructable* dest = getWorld()->getComponent<Destructable>(entity).value_or(nullptr);
    if(dest)
        components.insert("destructable", dest->toJson());

    Camera* camera = getWorld()->getComponent<Camera>(entity).value_or(nullptr);
    if(camera)
        components.insert("camera", camera->toJson());

    // Legg til flere komponenter her etterhvert
    entityObject.insert("id", entity);
    entityObject.insert("components", components);

    entities_.push_back(entityObject);

}
}

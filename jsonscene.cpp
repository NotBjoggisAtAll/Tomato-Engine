#include "jsonscene.h"
#include <QFile>
#include <QJsonDocument>
#include "World.h"
#include "Components/allcomponents.h"
namespace jba {


JsonScene::JsonScene(QString SceneName)
{
    sceneObject_.insert("scene", SceneName);
}

void JsonScene::makeFile(QString FilePath, bool overwrite)
{
    QFile file(FilePath);
    QJsonDocument doc;
    sceneObject_.insert("entities", entities_);
    doc.setObject(sceneObject_);

    if(file.exists() && !overwrite)
        return;
    else
        file.remove();

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
    // Legg til flere komponenter her etterhvert
    entityObject.insert("id", entity);
    entityObject.insert("components", components);

    entities_.push_back(entityObject);

}
}

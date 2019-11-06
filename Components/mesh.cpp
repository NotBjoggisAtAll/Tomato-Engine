#include "mesh.h"
#include <QJsonObject>
#include "resourcefactory.h"

Mesh::Mesh(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Mesh::toJson()
{
    QJsonObject object;
    object.insert("visible", isVisible_);
    object.insert("filepath", QString::fromStdString(filepath_));
    return object;
}


void Mesh::fromJson(QJsonObject Json)
{
    *this = ResourceFactory::get()->loadMesh(Json.take("filepath").toString().toStdString());
    isVisible_ = Json.take("visible").toBool();
}

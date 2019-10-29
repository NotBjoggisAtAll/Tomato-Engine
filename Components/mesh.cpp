#include "mesh.h"
#include <QJsonObject>
#include "resourcefactory.h"

Mesh::Mesh(QJsonObject JSON)
{
    *this = ResourceFactory::get()->loadMesh(JSON.take("filepath").toString().toStdString());
}

QJsonObject Mesh::toJson()
{
    QJsonObject object;
    object.insert("visible", isVisible_);
    object.insert("filepath", QString::fromStdString(filepath_));
    return object;
}

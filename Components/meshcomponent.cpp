#include "meshcomponent.h"
#include "resourcefactory.h"

Mesh::Mesh(QJsonObject JSON)
{
    *this = ResourceFactory::instance()->loadMesh(JSON.take("filepath").toString().toStdString()).first;
}

QJsonObject Mesh::toJSON()
{
    QJsonObject object;
    object.insert("visible", isVisible);
    object.insert("filepath", QString::fromStdString(filepath_));

    return object;
}

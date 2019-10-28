#include "collision.h"
#include "resourcefactory.h"
#include <QJsonObject>

Collision::Collision(QJsonObject JSON)
{
    *this = ResourceFactory::instance()->loadMesh(JSON.take("filepath").toString().toStdString()).second;
}

QJsonObject Collision::toJSON()
{
    QJsonObject object;
    object.insert("filepath", QString::fromStdString(filepath_));
    return object;
}

#include "collision.h"
#include "resourcefactory.h"
#include <QJsonObject>

Collision::Collision(QJsonObject JSON)
{
    *this = ResourceFactory::get()->getCollision(JSON.take("filepath").toString().toStdString());
}

QJsonObject Collision::toJSON()
{
    QJsonObject object;
    object.insert("filepath", QString::fromStdString(filepath_));
    return object;
}

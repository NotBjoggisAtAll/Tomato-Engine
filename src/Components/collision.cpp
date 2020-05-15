#include "collision.h"
#include "Factories/resourcefactory.h"
#include <QJsonObject>

Collision::Collision(gsl::Vector3D minVector, gsl::Vector3D maxVector) : minVector_(minVector), maxVector_(maxVector), scaledMinVector_(minVector), scaledMaxVector_(maxVector) {}

Collision::Collision(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Collision::toJson()
{
    QJsonObject object;
    object.insert("filepath", QString::fromStdString(filepath_));
    return object;
}

void Collision::fromJson(QJsonObject Json)
{
    *this = ResourceFactory::get()->getCollision(Json.take("filepath").toString().toStdString());
}

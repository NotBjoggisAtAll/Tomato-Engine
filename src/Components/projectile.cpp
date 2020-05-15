#include "projectile.h"

Projectile::Projectile(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Projectile::toJson()
{
    QJsonObject object;

    object.insert("speed", static_cast<double>(speed_));
    object.insert("lifetime", static_cast<double>(lifetime_));
    return object;
}

void Projectile::fromJson(QJsonObject Json)
{
    speed_ = static_cast<float>(Json.take("speed").toDouble());
    lifetime_ = static_cast<float>(Json.take("lifetime").toDouble());
}

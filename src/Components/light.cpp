#include "light.h"
#include <QJsonObject>
#include <QJsonArray>

Light::Light(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Light::toJson()
{
    QJsonObject object;

    QJsonObject ambientObject;
    QJsonArray ambientColor;
    ambientColor.insert(0, QJsonValue(static_cast<double>(ambientColor_.x)));
    ambientColor.insert(1, QJsonValue(static_cast<double>(ambientColor_.y)));
    ambientColor.insert(2, QJsonValue(static_cast<double>(ambientColor_.z)));

    ambientObject.insert("strength", static_cast<double>(ambientStrength_));
    ambientObject.insert("color", ambientColor);

    QJsonObject lightObject;
    QJsonArray lightColor;
    lightColor.insert(0, QJsonValue(static_cast<double>(lightColor_.x)));
    lightColor.insert(1, QJsonValue(static_cast<double>(lightColor_.y)));
    lightColor.insert(2, QJsonValue(static_cast<double>(lightColor_.z)));

    lightObject.insert("strength", static_cast<double>(lightStrength_));
    lightObject.insert("color", lightColor);

    QJsonObject specularObject;
    specularObject.insert("strength", static_cast<double>(specularStrength_));
    specularObject.insert("exponent", specularExponent_);

    object.insert("ambient", ambientObject);
    object.insert("light", lightObject);
    object.insert("specular", specularObject);

    return object;
}


void Light::fromJson(QJsonObject Json)
{
    if(!Json.contains("ambient")) return;

    QJsonObject ambientObject = Json.take("ambient").toObject();

    ambientStrength_ = static_cast<float>(ambientObject.take("strength").toDouble());
    QJsonArray ambientColor = ambientObject.take("color").toArray();
    ambientColor_.x = static_cast<float>(ambientColor.at(0).toDouble());
    ambientColor_.y = static_cast<float>(ambientColor.at(1).toDouble());
    ambientColor_.z = static_cast<float>(ambientColor.at(2).toDouble());

    QJsonObject lightObject = Json.take("light").toObject();

    lightStrength_ = static_cast<float>(lightObject.take("strength").toDouble());
    QJsonArray lightColor = lightObject.take("color").toArray();
    lightColor_.x = static_cast<float>(lightColor.at(0).toDouble());
    lightColor_.y = static_cast<float>(lightColor.at(1).toDouble());
    lightColor_.z = static_cast<float>(lightColor.at(2).toDouble());

    QJsonObject specularObject = Json.take("specular").toObject();

    specularStrength_ = static_cast<float>(specularObject.take("strength").toDouble());
    specularExponent_ = specularObject.take("exponent").toInt();
}

#include "input.h"

Input::Input(bool isControlable) : isControllable(isControlable) {}

Input::Input(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Input::toJson()
{
    QJsonObject object;
    object.insert("controlable", isControllable);
    return object;
}

void Input::fromJson(QJsonObject Json)
{
    if(!Json.contains("controlable")) return;
    isControllable = Json.take("controlable").toBool();
}

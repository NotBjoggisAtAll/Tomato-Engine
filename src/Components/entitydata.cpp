#include "entitydata.h"
#include <utility>
#include <QJsonObject>
#include <QJsonArray>

EntityData::EntityData(std::string Name) : name_(std::move(Name)) {}

EntityData::EntityData(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject EntityData::toJson()
{
    QJsonObject Object;
    Object.insert("name", QString::fromStdString(name_));
    Object.insert("parent", parent_);
    return Object;
}

void EntityData::fromJson(QJsonObject Json)
{
    if(!Json.contains("name") || !Json.contains("parent"))
        return;

    name_ = Json.take("name").toString().toStdString();
    parent_ = Json.take("parent").toInt();

}

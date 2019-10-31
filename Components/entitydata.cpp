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
    QJsonArray childrenArray;
    for(unsigned int i = 0; i < children_.size(); ++i)
        childrenArray.insert(static_cast<int>(i),children_.at(i));
    Object.insert("children", childrenArray);
    return Object;
}

void EntityData::fromJson(QJsonObject Json)
{
    if(!Json.contains("name") || !Json.contains("parent") ||!Json.contains("children"))
        return;

    name_ = Json.take("name").toString().toStdString();
    parent_ = Json.take("parent").toInt();
    QJsonArray array =  Json.take("children").toArray();
    for(QJsonValue val : array)
        children_.push_back(val.toInt());
}

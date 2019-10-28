#include "entitydata.h"
#include <utility>
#include <QJsonObject>
#include <QJsonArray>

EntityData::EntityData(std::string Name) : name_(std::move(Name)) {}

EntityData::EntityData(QJsonObject JSON)
{
    name_ = JSON.take("name").toString().toStdString();
    parent_ = JSON.take("parent").toInt();
    QJsonArray array =  JSON.take("children").toArray();
    for(QJsonValue val : array)
        children_.push_back(val.toInt());
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

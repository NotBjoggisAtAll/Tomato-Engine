#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "types.h"
#include <vector>
#include <utility>
#include <QJsonObject>
#include <QJsonArray>

struct EntityData{

    EntityData() = default;
    EntityData(std::string Name) : name(std::move(Name)) {}

    std::string name;

    Entity parent{-1};
    std::vector<Entity> children;

    EntityData(QJsonObject JSON)
    {
        name = JSON.take("name").toString().toStdString();
        parent = JSON.take("parent").toInt();
        QJsonArray array =  JSON.take("children").toArray();
        for(QJsonValue val : array)
            children.push_back(val.toInt());
    }

    QJsonObject toJSON()
    {
        QJsonObject Object;
        Object.insert("name", QString::fromStdString(name));
        Object.insert("parent", parent);
        QJsonArray childrenArray;
        for(unsigned int i = 0; i < children.size(); ++i)
            childrenArray.insert(static_cast<int>(i),children.at(i));
        Object.insert("children", childrenArray);
        return Object;
    }
};

#endif // ENTITYDATA_H

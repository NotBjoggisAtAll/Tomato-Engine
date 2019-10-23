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
        name = JSON.take("Name").toString().toStdString();
        parent = JSON.take("Parent").toInt();
        QJsonArray array =  JSON.take("Children").toArray();
        for(QJsonValue val : array)
            children.push_back(val.toInt());
    }

    QJsonObject toJSON()
    {
        QJsonObject Object;
        Object.insert("Name", QString::fromStdString(name));
        Object.insert("Parent", parent);
        QJsonArray childrenArray;
        for(unsigned int i = 0; i < children.size(); ++i)
            childrenArray.insert(static_cast<int>(i),children.at(i));
        Object.insert("Children", childrenArray);
        return Object;
    }
};

#endif // ENTITYDATA_H

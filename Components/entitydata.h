#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "types.h"
#include <vector>

class QJsonObject;

struct EntityData{

    EntityData() = default;
    EntityData(std::string Name);
    EntityData(QJsonObject JSON);

    std::string name_;
    Entity parent_{-1};
    std::vector<Entity> children_;

    QJsonObject toJson();

};

#endif // ENTITYDATA_H

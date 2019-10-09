#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "types.h"
#include <vector>

struct EntityData{

    EntityData() {}
    EntityData(std::string Name) : name(Name) {}

    std::string name;

    Entity parent{-1};
    std::vector<Entity> children;
};

#endif // ENTITYDATA_H

#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "types.h"
#include <vector>
#include <utility>

struct EntityData{

    EntityData() = default;
    EntityData(std::string Name) : name(std::move(Name)) {}

    std::string name;

    Entity parent{-1};
    std::vector<Entity> children;
};

#endif // ENTITYDATA_H

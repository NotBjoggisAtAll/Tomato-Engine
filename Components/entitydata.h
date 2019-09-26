#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "types.h"

struct EntityData{

    EntityData() {}
    EntityData(std::string Name) : name(Name) {}

    std::string name;

    Entity parent{-1};
};

#endif // ENTITYDATA_H

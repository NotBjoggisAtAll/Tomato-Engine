#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include "types.h"

struct System
{
    System() = default;
    virtual ~System() = default;

    virtual void beginPlay(){}
    virtual void tick(){}

    std::set<Entity> mEntities;
};

#endif // SYSTEM_H

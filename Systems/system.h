#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include "types.h"
#include <QObject>
struct System : public QObject
{
    Q_OBJECT
public:
    System() = default;
    virtual ~System() = default;

    virtual void beginPlay(){}
    virtual void tick(){}

    std::set<Entity> mEntities;
};

#endif // SYSTEM_H

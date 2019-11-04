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
    virtual void endPlay(){}


    std::set<Entity> entities_;
};

#endif // SYSTEM_H

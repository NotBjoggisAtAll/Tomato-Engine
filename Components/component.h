#ifndef COMPONENT_H
#define COMPONENT_H

#include <QJsonObject>

struct Component
{
    virtual ~Component();
    virtual QJsonObject toJson() = 0;
    virtual void fromJson(QJsonObject Json) = 0;
};

#endif // COMPONENT_H

#ifndef DESTRUCTABLE_H
#define DESTRUCTABLE_H

#include "component.h"

struct Destructable : public Component
{
    Destructable(){}
    Destructable(bool destructable) : isDestructable(destructable) {}
    Destructable(QJsonObject Json){fromJson(Json);}

    QJsonObject toJson() override
    {
        QJsonObject object;
        object.insert("destructable", isDestructable);
        return object;
    }

    void fromJson(QJsonObject Json) override
    {
        isDestructable = Json.take("destructable").toBool();
    }

    bool isDestructable = true;
};
#endif // DESTRUCTABLE_H

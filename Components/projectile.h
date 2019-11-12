#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Components/component.h"
#include "GSL/vector3d.h"

struct Projectile : public Component
{
    Projectile();
    ~Projectile() override;

    gsl::Vector3D direction_ = gsl::Vector3D(0);
    float speed_ = 5;
    bool routeCalculated = false;
    float lifetime_ = 1.f;

    virtual QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // PROJECTILE_H

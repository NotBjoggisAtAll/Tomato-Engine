#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "system.h"
#include "GSL/vector3d.h"

class MovementSystem : public System
{
public:
    MovementSystem() = default;

    void addPosition(Entity entity, gsl::Vector3D translation);

    void setPosition(Entity entity, gsl::Vector3D position);
    void setScale(Entity entity, gsl::Vector3D scale);
};

#endif // MOVEMENTSYSTEM_H

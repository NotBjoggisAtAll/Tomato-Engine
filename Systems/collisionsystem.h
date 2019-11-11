#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "system.h"

#include "GSL/vector3d.h"

class Collision;
class Transform;

class CollisionSystem : public System
{
    Q_OBJECT
public:
    CollisionSystem() = default;

    void tick() override;
    Entity checkMouseCollision(gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection);

signals:
    void entitiesCollided(Entity entity1, Entity entity2);

private:
    bool intersect(Collision *collision, Transform *transform, gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, float &distance);

};

#endif // COLLISIONSYSTEM_H

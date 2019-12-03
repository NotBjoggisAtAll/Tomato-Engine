#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "system.h"

#include "GSL/vector3d.h"
#include "GSL/vector2d.h"
#include "hitresult.h"

struct Collision;
struct Transform;

class CollisionSystem : public System
{
    Q_OBJECT
public:
    CollisionSystem() = default;

    void tick(float deltaTime) override;

    bool checkMouseCollision2D(gsl::Vector2D mousePos, gsl::Vector2D screenWidthHeight, HitResult2D &hit);
    bool checkMouseCollision(gsl::Vector2D mousePos, gsl::Vector2D screenWidthHeight, HitResult &hit);
signals:
    void entitiesCollided(Entity entity1, Entity entity2);

private:
    bool raycastFromMouse(gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, HitResult &hit);
    bool intersect(Collision *collision, Transform *transform, gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, HitResult &result);

};

#endif // COLLISIONSYSTEM_H

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "system.h"

#include "GSL/vector3d.h"
#include "GSL/vector2d.h"
#include "hitresult.h"

struct Collision;
struct Transform;

/**
 * The CollisionSystem's main responsibility is to check if two objects has collided.
 * But the system also contains some functions used for mousepicking when the user is clicking with the left mouse button.
 */
class CollisionSystem : public System
{
    Q_OBJECT
public:

    /**
     * Default constructor.
     */
    CollisionSystem() = default;

    /**
     * Tick runs every frame.
     * Checks all entities with a collision box if they has collided or not.
     * If true, runs the signal entitesCollided with the two entities collided.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    void tick(float deltaTime) override;

    /**
     * Used to check if the mouse has clicked on something in the 2D space. (Buttons).
     * Calculates the mousepos over to local clip space (-1 and 1).
     * @param mousePos - The mouse position when clicked.
     * @param screenWidthHeight - The screen's width and height. (x = width, y = heigth).
     * @param hit OUT parameter. Returns information about what the mouse has hit.
     * @return true if the mouse has collided with something in the 2D space.
     */
    bool checkMouseCollision2D(gsl::Vector2D mousePos, gsl::Vector2D screenWidthHeight, HitResult2D &hit);

    /**
     * Used to check if the mouse has clicked on something in the 3D space.
     * Uses the raycastFromMouse function to calculate what the mouse hits.
     * @param mousePos - The mouse position when clicked.
     * @param screenWidthHeight - The screen's width and height. (x = width, y = heigth).
     * @param hit OUT parameter. Returns information about what the mouse has hit.
     * @return true if the mouse has collided with something in the 3D space.
     */
    bool checkMouseCollision(gsl::Vector2D mousePos, gsl::Vector2D screenWidthHeight, HitResult &hit);

signals:
    /**
     * Ran if 2 entities has collided.
     * @param entity1 - Entity.
     * @param entity2 - Entity.
     */
    void entitiesCollided(Entity entity1, Entity entity2);

private:

    /**
     * Shoots a ray from the rayOrigin in the rayDirection.
     * Loops trough all entites in the scene.
     * Stops at the first target hit.
     * Uses the intersect function as help to check if it collided with something or not.
     * @param rayOrigin - The start position of the ray.
     * @param rayDirection - The direction of the ray.
     * @param hit OUT parameter. Returns information about what the mouse has hit.
     * @return true if the mouse has collided with something in the 3D space.
     */
    bool raycastFromMouse(gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, HitResult &hit);

    /**
     *
     * @param collision - The Collision component of the current Entity to check.
     * @param transform - The Transform component of the current Entity to check
     * @param rayOrigin - The start position of the ray.
     * @param rayDirection - The direction of the ray.
     * @param result OUT parameter. Returns information about what the mouse has hit.
     * @return true if the mouse has collided with something in the 3D space.
     */
    bool intersect(Collision *collision, Transform *transform, gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, HitResult &result);
};

#endif // COLLISIONSYSTEM_H

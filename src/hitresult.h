#ifndef HITRESULT_H
#define HITRESULT_H

#include "GSL/vector3d.h"
#include "GSL/vector2d.h"
#include "types.h"

/**
 * The HitResult struct contains information about what the raycast hit.
 */
struct HitResult
{
    /// The entity that the ray hit.
    Entity entityHit = -1;

    /// The distance between the rayOrigin and where the entity is.
    float distance = 0;

    /// The position of the entity hit.
    gsl::Vector3D position = gsl::Vector3D(0);
};

/**
 * The HitResult2D struct contains information about what the raycast hit.
 */
struct HitResult2D
{
    /// The entity that the ray hit.
    Entity entityHit = -1;

    /// The position of the entity hit.
    gsl::Vector2D entityPosition = gsl::Vector2D(0);
};

#endif // HITRESULT_H

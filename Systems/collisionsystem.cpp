#include "collisionsystem.h"
#include "World.h"
#include "Components/collision.h"
#include "Components/transformcomponent.h"
#include "Components/entitydata.h"

void CollisionSystem::checkCollision()
{
    for (auto const& entity : mEntities)
    {

        auto collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        auto data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);

        if(!collision || !transform || !data)
            continue;

        for(auto const& otherEntity : mEntities)
        {
            if(otherEntity == entity)
                continue;

            auto otherCollision = getWorld()->getComponent<Collision>(otherEntity).value_or(nullptr);
            auto otherTransform = getWorld()->getComponent<Transform>(otherEntity).value_or(nullptr);
            auto otherData = getWorld()->getComponent<EntityData>(otherEntity).value_or(nullptr);

            if(!otherCollision || !otherTransform || !otherData)
                continue;



            auto Cube1Max = transform->position + (collision->scaledMaxVector_ );
            auto Cube1Min = transform->position + collision->scaledMinVector_;
            auto Cube2Max = otherTransform->position + otherCollision->scaledMaxVector_;
            auto Cube2Min = otherTransform->position + otherCollision->scaledMinVector_;

            if ((Cube1Min.x <= Cube2Max.x && Cube1Max.x >= Cube2Min.x) &&
                    (Cube1Min.y <= Cube2Max.y && Cube1Max.y >= Cube2Min.y) &&
                    (Cube1Min.z <= Cube2Max.z && Cube1Max.z >= Cube2Min.z))
            {
                qDebug() << QString::fromStdString(data->name + " collides with " + otherData->name);
                break;
            }

        }
    }
}

Entity CollisionSystem::checkMouseCollision(gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection)
{
    Entity entityToReturn = -1;
    float distance = 999999999.f;
    for (auto& entity : mEntities)
    {
        auto collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        auto data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);

        if(!collision || !transform || !data)
            continue;

        float tempDistance = 0.f;

        if(intersect(collision, transform, rayOrigin, rayDirection,tempDistance))
        {
            if(tempDistance < distance)
            {
                distance = tempDistance;
                entityToReturn = entity;
            }
        }
    }
    return entityToReturn;
}

bool CollisionSystem::intersect(Collision* collision, Transform* transform, gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, float& distance)
{

    gsl::Vector3D dirfrac;
    // r.dir is unit direction vector of ray
    dirfrac.x = 1.0f / rayDirection.x;
    dirfrac.y = 1.0f / rayDirection.y;
    dirfrac.z = 1.0f / rayDirection.z;

    gsl::Vector3D lb = transform->position + collision->scaledMinVector_;
    gsl::Vector3D rb = transform->position + collision->scaledMaxVector_;

    // lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
    // r.org is origin of ray
    float t1 = (lb.x - rayOrigin.x)*dirfrac.x;
    float t2 = (rb.x - rayOrigin.x)*dirfrac.x;
    float t3 = (lb.y - rayOrigin.y)*dirfrac.y;
    float t4 = (rb.y - rayOrigin.y)*dirfrac.y;
    float t5 = (lb.z - rayOrigin.z)*dirfrac.z;
    float t6 = (rb.z - rayOrigin.z)*dirfrac.z;

    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0)
    {
        distance = -1;
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        distance = -1;
        return false;
    }

    distance = tmin;
    return true;
}


#include "collisionsystem.h"
#include "world.h"
#include "Components/collision.h"
#include "Components/transform.h"
#include "Components/entitydata.h"
#include "GSL/matrix4x4.h"

void CollisionSystem::tick()
{
    for (auto const& entity : entities_)
    {

        auto collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        auto data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);

        if(!collision || !transform || !data)
            continue;

        if(collision->minVector_ == gsl::Vector3D(0) && collision->maxVector_ == gsl::Vector3D(0))
            continue;

        if(collision->scaledMaxVector_ == gsl::Vector3D(0) && collision->scaledMinVector_ == gsl::Vector3D(0))
        {
            //Hvis disse for en eller annen grunn er 0 lag nye
            gsl::Matrix4x4 tempMatrix;
            tempMatrix.scale(transform->scale_);

            collision->scaledMaxVector_ = (tempMatrix * gsl::Vector4D(collision->maxVector_,0)).getXYZ();
            collision->scaledMinVector_ = (tempMatrix * gsl::Vector4D(collision->minVector_,0)).getXYZ();
        }

        for(auto const& otherEntity : entities_)
        {
            if(otherEntity == entity)
                continue;

            auto otherCollision = getWorld()->getComponent<Collision>(otherEntity).value_or(nullptr);
            auto otherTransform = getWorld()->getComponent<Transform>(otherEntity).value_or(nullptr);
            auto otherData = getWorld()->getComponent<EntityData>(otherEntity).value_or(nullptr);

            if(!otherCollision || !otherTransform || !otherData)
                continue;

            if(otherCollision->minVector_ == gsl::Vector3D(0) && otherCollision->maxVector_ == gsl::Vector3D(0))
                continue;

            auto Cube1Max = transform->position_ + (collision->scaledMaxVector_ );
            auto Cube1Min = transform->position_ + collision->scaledMinVector_;
            auto Cube2Max = otherTransform->position_ + otherCollision->scaledMaxVector_;
            auto Cube2Min = otherTransform->position_ + otherCollision->scaledMinVector_;

            if ((Cube1Min.x <= Cube2Max.x && Cube1Max.x >= Cube2Min.x) &&
                    (Cube1Min.y <= Cube2Max.y && Cube1Max.y >= Cube2Min.y) &&
                    (Cube1Min.z <= Cube2Max.z && Cube1Max.z >= Cube2Min.z))
            {
                qDebug() << QString::fromStdString(data->name_ + " collides with " + otherData->name_);
                break;
            }

        }
    }
}

Entity CollisionSystem::checkMouseCollision(gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection)
{
    Entity entityToReturn = -1;
    float distance = 999999999.f;
    for (auto& entity : entities_)
    {
        auto collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        auto data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);

        if(!collision || !transform || !data)
            continue;

        if(collision->scaledMaxVector_ == gsl::Vector3D(0) && collision->scaledMinVector_ == gsl::Vector3D(0))
        {
            //Hvis disse for en eller annen grunn er 0 lag nye
            gsl::Matrix4x4 tempMatrix;
            tempMatrix.scale(transform->scale_);

            collision->scaledMaxVector_ = (tempMatrix * gsl::Vector4D(collision->maxVector_,0)).getXYZ();
            collision->scaledMinVector_ = (tempMatrix * gsl::Vector4D(collision->minVector_,0)).getXYZ();
        }

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

    gsl::Vector3D lb = transform->position_ + collision->scaledMinVector_;
    gsl::Vector3D rb = transform->position_ + collision->scaledMaxVector_;

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


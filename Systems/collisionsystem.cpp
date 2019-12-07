#include "collisionsystem.h"
#include "world.h"
#include "Components/collision.h"
#include "Components/gui.h"
#include "Components/transform.h"
#include "GSL/matrix4x4.h"
#include "Components/camera.h"

#include "GSL/gsl_math_extensions.h"

void CollisionSystem::tick(float deltaTime)
{
    for (auto const& entity : entities_)
    {

        auto collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);

        if(!collision || !transform)
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

            if(!otherCollision || !otherTransform)
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
                emit entitiesCollided(entity, otherEntity);
                break;
            }

        }
    }
}
bool CollisionSystem::checkMouseCollision2D(gsl::Vector2D mousePos, gsl::Vector2D screenWidthHeight, HitResult2D& hit)
{
    gsl::Vector2D newMouse = gsle::map(gsl::Vector2D(mousePos.x, mousePos.y),
                                       gsl::Vector2D(0,0),
                                       gsl::Vector2D(screenWidthHeight.x,screenWidthHeight.y),
                                       gsl::Vector2D(-1,-1),
                                       gsl::Vector2D(1,1));

    newMouse.y = -newMouse.y;

    for(const auto& entity : getWorld()->getEntities())
    {
        auto gui = getWorld()->getComponent<GUI>(entity).value_or(nullptr);

        if(gui)
        {
            gsl::Vector2D guipos = gsl::Vector2D(
                        (gui->scale_.x * screenWidthHeight.y)/
                        screenWidthHeight.x,gui->scale_.y);

            gsl::Vector2D guiMIN = gui->position_ - guipos;
            gsl::Vector2D guiMAX = gui->position_ + guipos;


            if ((newMouse.x <= guiMAX.x && newMouse.x >= guiMIN.x) &&
                    (newMouse.y <= guiMAX.y && newMouse.y >= guiMIN.y))
            {
                hit.entityHit = entity;
                hit.entityPosition = guipos;
                return true;
            }
        }
    }
    return false;
}

bool CollisionSystem::checkMouseCollision(gsl::Vector2D mousePos, gsl::Vector2D screenWidthHeight, HitResult& hit)
{
    auto camera = getWorld()->getComponent<Camera>(getWorld()->getCurrentCamera()).value_or(nullptr);
    auto transform = getWorld()->getComponent<Transform>(getWorld()->getCurrentCamera()).value_or(nullptr);

    float x = (2.0f * mousePos.x) / screenWidthHeight.x - 1.0f;
    float y = 1.0f - (2.0f * mousePos.y) / screenWidthHeight.y;
    float z = 1.0f;
    gsl::Vector3D ray_nds(x, y, z); //nds = normalised device coordinates
    gsl::Vector4D ray_clip(ray_nds.x, ray_nds.y, -1.0f, 1.0f); //clip = Homogeneous Clip Coordinates
    gsl::Matrix4x4 projection_matrix = camera->projectionMatrix_;
    projection_matrix.inverse();
    gsl::Vector4D ray_eye = projection_matrix * ray_clip;
    ray_eye.z = -1.0f;
    ray_eye.w = 0.0f;
    gsl::Matrix4x4 view_matrix = camera->viewMatrix_;
    view_matrix.inverse();
    gsl::Vector3D ray_world = (view_matrix * ray_eye).toVector3D();
    ray_world.normalize();

    return raycastFromMouse(transform->position_,ray_world,hit);
}

bool CollisionSystem::raycastFromMouse(gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, HitResult& hit)
{
    float distance = 999999999.f;
    for (auto& entity : entities_)
    {
        auto collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);

        if(!collision || !transform)
            continue;

        if(collision->scaledMaxVector_ == gsl::Vector3D(0) && collision->scaledMinVector_ == gsl::Vector3D(0))
        {
            //Hvis disse for en eller annen grunn er 0 lag nye
            gsl::Matrix4x4 tempMatrix;
            tempMatrix.scale(transform->scale_);

            collision->scaledMaxVector_ = (tempMatrix * gsl::Vector4D(collision->maxVector_,0)).getXYZ();
            collision->scaledMinVector_ = (tempMatrix * gsl::Vector4D(collision->minVector_,0)).getXYZ();
        }

        if(intersect(collision, transform, rayOrigin, rayDirection,hit))
        {
            if(hit.distance < distance)
            {
                distance = hit.distance;
                hit.entityHit = entity;
                return true;
            }
        }
    }
    return false;
}

bool CollisionSystem::intersect(Collision* collision, Transform* transform, gsl::Vector3D rayOrigin, gsl::Vector3D rayDirection, HitResult &result)
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
        result.distance = -1;
        return false;
    }

    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
    {
        result.distance = -1;
        return false;
    }

    result.distance = tmin;
    result.position = rayOrigin + rayDirection * tmin;
    return true;
}

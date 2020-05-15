#include "projectilesystem.h"
#include "Components/transform.h"
#include "Components/projectile.h"
#include "Components/npc.h"
#include "Components/bspline.h"
#include "world.h"
#include <vector>
#include <algorithm>

void ProjectileSystem::tick(float deltaTime)
{
    for(const auto& entity: entities_)
    {
        auto projectile = getWorld()->getComponent<Projectile>(entity).value();

        if(!projectile->active_) continue;
        auto projcetileTransform = getWorld()->getComponent<Transform>(entity).value();


        projcetileTransform->position_ += projectile->direction_ * projectile->speed_ * deltaTime;
        projectile->lifetime_ -= deltaTime;
        if(projectile->lifetime_ < 0)
            entitiesToBeDeleted_.push(entity);

    }
    while(!entitiesToBeDeleted_.empty())
    {
      //  getWorld()->destroyEntityLater(entitiesToBeDeleted_.front());
        auto projcetileTransform = getWorld()->getComponent<Transform>(entitiesToBeDeleted_.front()).value();
        projcetileTransform->position_ = gsl::Vector3D(1000,0,0);
        auto projectile = getWorld()->getComponent<Projectile>(entitiesToBeDeleted_.front()).value();
        projectile->active_ = false;
        Projectile p;
        projectile->lifetime_ = p.lifetime_;
        entitiesToBeDeleted_.pop();
    }
}

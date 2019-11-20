#include "projectilesystem.h"
#include "Components/transform.h"
#include "Components/projectile.h"
#include "Components/npc.h"
#include "Components/bspline.h"
#include "world.h"
#include <vector>
#include <algorithm>

ProjectileSystem::ProjectileSystem()
{

}


void ProjectileSystem::beginPlay()
{

}

void ProjectileSystem::tick(float deltaTime)
{
    for(const auto& entity: entities_)
    {
        auto projectile = getWorld()->getComponent<Projectile>(entity).value();
        auto projcetileTransform = getWorld()->getComponent<Transform>(entity).value();

        if(!projectile->routeCalculated)
        {
            if(projectile->npcPositions_.empty()) return;

            auto lowest = std::min_element(projectile->npcPositions_.begin(), projectile->npcPositions_.end(),[&](const gsl::Vector3D& npc1, const gsl::Vector3D& npc2 )
            {
                return (npc1 - projcetileTransform->position_).length() <
                        (npc2 - projcetileTransform->position_).length();
            });

            projectile->direction_ = (*lowest - projcetileTransform->position_).normalized();
            projectile->direction_.y = 0;
            projectile->routeCalculated = true;
        }
        else
        {
            projcetileTransform->position_ += projectile->direction_ * projectile->speed_ * deltaTime;
            projectile->lifetime_ -= deltaTime;
            if(projectile->lifetime_ < 0)
                entitiesToBeDeleted_.push(entity);
        }
    }
    while(!entitiesToBeDeleted_.empty())
    {
        getWorld()->destroyEntityLater(entitiesToBeDeleted_.front());
        entitiesToBeDeleted_.pop();
    }

}

void ProjectileSystem::endPlay()
{
}


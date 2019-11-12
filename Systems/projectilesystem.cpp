#include "projectilesystem.h"
#include "Components/transform.h"
#include "Components/projectile.h"
#include "Components/npc.h"
#include "Components/bspline.h"
#include "world.h"
#include <vector>

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

            std::vector<Entity> npcs;
            for(const auto& entity : getWorld()->getEntities())
            {
                auto npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
                if(!npc) continue;
                npcs.push_back(entity);
            }
            if(npcs.empty()) return;

            std::sort(npcs.begin(), npcs.end(), [&](const int& npc1, const int& npc2 )
            {
                auto transform1 = getWorld()->getComponent<Transform>(npc1).value_or(nullptr);
                auto transform2 = getWorld()->getComponent<Transform>(npc2).value_or(nullptr);

                return (transform1->position_ - projcetileTransform->position_).length() <
                        (transform2->position_ - projcetileTransform->position_).length();

            });

            //Shoot at nearest
            auto transform1 = getWorld()->getComponent<Transform>(npcs[0]).value_or(nullptr);
            projectile->direction_ = (transform1->position_ - projcetileTransform->position_).normalized();
            projectile->direction_.y = 0;
            projectile->routeCalculated = true;
        }else
        {
            projcetileTransform->position_ += projectile->direction_ * projectile->speed_ * deltaTime;
            projectile->lifetime_ -= deltaTime;
            if(projectile->lifetime_ < 0)
                entitiesToBeDeleted_.push(entity);
        }
    }
    while(!entitiesToBeDeleted_.empty())
    {
        getWorld()->destroyEntity(entitiesToBeDeleted_.front());
        entitiesToBeDeleted_.pop();
    }

}

void ProjectileSystem::endPlay()
{
}


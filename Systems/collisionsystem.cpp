#include "collisionsystem.h"
#include "World.h"
#include "Components/collision.h"
#include "Components/transformcomponent.h"
#include "Components/entitydata.h"

CollisionSystem::CollisionSystem()
{

}

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

void CollisionSystem::checkMouseCollision(gsl::Vector3D mousePosition)
{

}

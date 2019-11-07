#include "npcsystem.h"
#include "world.h"
#include "Components/npc.h"
#include "Components/transform.h"
#include "Components/vertexdata.h"
#include "bsplinecurve.h"

NpcSystem::NpcSystem()
{

}


void NpcSystem::beginPlay()
{
}

void NpcSystem::tick()
{
    for(const auto& entity : entities_)
    {
        auto npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);

        if(!npc) continue;
        if(!npc->bSplineCurve) continue;

        npc->state_ = NPCstates::PATROL;
        switch (npc->state_) {
        case NPCstates::PATROL:
            patrol(entity, npc);
            break;
        default:
            break;
        }
    }
}

void NpcSystem::endPlay()
{
    currentT_ = 0;
}

void NpcSystem::patrol(Entity entity, Npc* npc)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if(!transform) return;

    currentT_ += npc->speed_/60;
    if(currentT_ > 0.0001f && currentT_ < 1.f)
    {
        transform->position_ = npc->bSplineCurve->curvePosition(currentT_);
        transform->position_.y = getHeightBaryc(entity, npc->terrainId);
    }
    else
    {
        npc->event = NPCevents::ENDPOINT_ARRIVED;
        notify(entity);
    }
}

void NpcSystem::notify(Entity entity, std::optional<gsl::Vector3D> index)
{
    auto npc = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
    if(!npc) return;

    switch (npc->event) {
    case NPCevents::ITEM_TAKEN:
        if(index.has_value()){
            removePoints = true;
            pointIndices.push(index.value());
        }
        break;
    case NPCevents::ENDPOINT_ARRIVED:
        npc->bSplineCurve->randomizeControlpoints();
        npc->speed_ = -npc->speed_;
        if(removePoints == true)
        {
            while(!pointIndices.empty())
            {
                npc->bSplineCurve->removeControlPoint(pointIndices.front());
                pointIndices.pop();
            }
            removePoints = false;
        }
        break;
    default:
        break;
    }
}

float NpcSystem::getHeightBaryc(Entity npc, Entity terrain)
{
    VertexData* vertexData = getWorld()->getComponent<VertexData>(terrain).value_or(nullptr);
    Transform* npcTransform = getWorld()->getComponent<Transform>(npc).value();
    Transform* terrainTransform = getWorld()->getComponent<Transform>(terrain).value_or(nullptr);

    if(!terrainTransform) return 0;
    if(!vertexData) return 0;

    for (unsigned int i = 0; i < vertexData->indices_.size(); i+=3)
    {
        gsl::Vector3D pos1;
        gsl::Vector3D pos2;
        gsl::Vector3D pos3;
        pos1 = vertexData->vertices_[vertexData->indices_[i+0]].mXYZ + terrainTransform->position_;
        pos2 = vertexData->vertices_[vertexData->indices_[i+2]].mXYZ + terrainTransform->position_;
        pos3 = vertexData->vertices_[vertexData->indices_[i+1]].mXYZ + terrainTransform->position_;

        gsl::Vector2D temp = gsl::Vector2D(npcTransform->position_.x, npcTransform->position_.z);
        gsl::Vector3D bar = temp.barycentricCoordinates(gsl::Vector2D(pos1.x,pos1.z),gsl::Vector2D(pos2.x, pos2.z), gsl::Vector2D(pos3.x,pos3.z));

        if(bar.x>=0 && bar.x<=1 && bar.y>=0 && bar.y<=1 && bar.z>=0 && bar.z <=1)
        {

            gsl::Vector3D pos =  pos1*bar.x + pos2*bar.y + pos3*bar.z;
            return pos.y;
        }
    }
    return 0;
}

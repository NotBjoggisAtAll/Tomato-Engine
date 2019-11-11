#include "inputsystem.h"
#include "eventhandler.h"
#include "world.h"
#include "Components/transform.h"
#include "Components/input.h"
#include "Components/vertexdata.h"
#include "Components/camera.h"

InputSystem::InputSystem()
{

}


void InputSystem::beginPlay()
{
}

void InputSystem::tick()
{
    auto cameraEntity = getWorld()->getCurrentCamera();
    if(cameraEntity == -1) return;

    auto camera = getWorld()->getComponent<Camera>(cameraEntity).value_or(nullptr);
    if(!camera) return;
    camera->speed_ = 0.f;  //cancel last frame movement
    if(eventHandler_->keys_[Qt::MouseButton::RightButton] == true)
    {
        auto transform = getWorld()->getComponent<Transform>(cameraEntity).value_or(nullptr);
        if(!transform) return;
        if(eventHandler_->keys_[Qt::Key_W] == true)
            camera->speed_ = -cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_S] == true)
            camera->speed_ = cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_D] == true)
            transform->position_ += camera->right_ * cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_A] == true)
            transform->position_ += camera->right_ * -cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_Q] == true)
            transform->position_.y += -cameraSpeed;
        if(eventHandler_->keys_[Qt::Key_E] == true)
            transform->position_.y += cameraSpeed;
    }else{
        if(!getWorld()->bGameRunning) return;
        for(const auto& entity : entities_)
        {
            auto input = getWorld()->getComponent<Input>(entity).value();
            if(!input->isControllable) continue;

            if(eventHandler_->keys_[Qt::Key_W] == true)
                addPosition(entity,{0,0,0.1f});
            if(eventHandler_->keys_[Qt::Key_S] == true)
                addPosition(entity,{0,0,-0.1f});
            if(eventHandler_->keys_[Qt::Key_D] == true)
                addPosition(entity,{-0.1f,0,0});
            if(eventHandler_->keys_[Qt::Key_A] == true)
                addPosition(entity,{0.1f,0,0});

            setYPosition(entity, getHeightBaryc(entity,terrainId));
        }
    }
}

void InputSystem::endPlay()
{
}

void InputSystem::setEventHandler(const std::shared_ptr<EventHandler> &eventHandler)
{
    eventHandler_ = eventHandler;
}
void InputSystem::setYPosition(Entity entity, float y)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if (!transform) return;

    transform->position_.y = y;
}
void InputSystem::addPosition(Entity entity, gsl::Vector3D translation)
{
    auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if (!transform) return;

    auto position = transform->position_;
    transform->position_ = position + translation;
}

float InputSystem::getHeightBaryc(Entity player, Entity terrain)
{
    VertexData* vertexData = getWorld()->getComponent<VertexData>(terrain).value_or(nullptr);
    Transform* terrainTransform = getWorld()->getComponent<Transform>(terrain).value_or(nullptr);
    Transform* playerTransform = getWorld()->getComponent<Transform>(player).value();

    if(!terrainTransform) return 0;
    if(!vertexData) return 0;

    for (unsigned int i = 0; i < vertexData->indices_.size(); i+=3)
    {
        gsl::Vector3D pos1 = vertexData->vertices_[vertexData->indices_[i+0]].mXYZ + terrainTransform->position_;
        gsl::Vector3D pos2 = vertexData->vertices_[vertexData->indices_[i+2]].mXYZ + terrainTransform->position_;
        gsl::Vector3D pos3 = vertexData->vertices_[vertexData->indices_[i+1]].mXYZ + terrainTransform->position_;

        gsl::Vector2D temp = gsl::Vector2D(playerTransform->position_.x, playerTransform->position_.z);
        gsl::Vector3D bar = temp.barycentricCoordinates(gsl::Vector2D(pos1.x,pos1.z),gsl::Vector2D(pos2.x, pos2.z), gsl::Vector2D(pos3.x,pos3.z));

        if(bar.x>=0 && bar.x<=1 && bar.y>=0 && bar.y<=1 && bar.z>=0 && bar.z <=1)
        {

            gsl::Vector3D pos =  pos1*bar.x + pos2*bar.y + pos3*bar.z;
            return pos.y;
        }
    }
    return 0;
}

float InputSystem::getHeightBaryc(gsl::Vector3D pos, Entity terrain)
{
    VertexData* vertexData = getWorld()->getComponent<VertexData>(terrain).value_or(nullptr);
    Transform* terrainTransform = getWorld()->getComponent<Transform>(terrain).value_or(nullptr);

    if(!terrainTransform) return 0;
    if(!vertexData) return 0;

    for (unsigned int i = 0; i < vertexData->indices_.size(); i+=3)
    {
        gsl::Vector3D pos1 = vertexData->vertices_[vertexData->indices_[i+0]].mXYZ + terrainTransform->position_;
        gsl::Vector3D pos2 = vertexData->vertices_[vertexData->indices_[i+2]].mXYZ + terrainTransform->position_;
        gsl::Vector3D pos3 = vertexData->vertices_[vertexData->indices_[i+1]].mXYZ + terrainTransform->position_;

        gsl::Vector2D temp = gsl::Vector2D(pos.x, pos.z);
        gsl::Vector3D bar = temp.barycentricCoordinates(gsl::Vector2D(pos1.x,pos1.z),gsl::Vector2D(pos2.x, pos2.z), gsl::Vector2D(pos3.x,pos3.z));

        if(bar.x>=0 && bar.x<=1 && bar.y>=0 && bar.y<=1 && bar.z>=0 && bar.z <=1)
        {

            gsl::Vector3D pos =  pos1*bar.x + pos2*bar.y + pos3*bar.z;
            return pos.y;
        }
    }
    return 0;
}

void InputSystem::setTerrainId(const Entity &value)
{
    terrainId = value;
}

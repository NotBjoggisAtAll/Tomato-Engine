#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "Systems/system.h"
#include <memory>
#include "GSL/vector3d.h"

class EventHandler;
class VertexData;

class InputSystem : public System
{
public:
    InputSystem();
    void beginPlay() override;
    void tick() override;
    void endPlay() override;

    void setEventHandler(const std::shared_ptr<EventHandler> &eventHandler);

    void setTerrainId(const Entity &value);

private:
    std::shared_ptr<EventHandler> eventHandler_;
    void addPosition(Entity entity, gsl::Vector3D translation);

    float cameraSpeed = 0.01f;

    float getHeightBaryc(Entity player, Entity terrain);
    void setYPosition(Entity entity, float y);

    Entity terrainId = -1;
};

#endif // INPUTSYSTEM_H

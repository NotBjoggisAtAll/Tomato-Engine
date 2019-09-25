#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "system.h"

class World;
class Camera;

class SoundSystem : public System
{
public:
    SoundSystem();

    void update(Camera *currCamera);

private:

    World* world{nullptr};
};

#endif // SOUNDSYSTEM_H

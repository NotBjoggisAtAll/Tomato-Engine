#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

class ResourceManager;
class Camera;

class SoundSystem
{
public:
    SoundSystem();

    ResourceManager* Factory{nullptr};
    void update(Camera *currCamera);
};

#endif // SOUNDSYSTEM_H

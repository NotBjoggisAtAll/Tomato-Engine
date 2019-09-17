#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

class ResourceManager;
class Camera;

class SoundSystem
{
public:
    SoundSystem();

    void update(Camera *currCamera);

private:
    ResourceManager* Factory{nullptr};
};

#endif // SOUNDSYSTEM_H

#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "system.h"

class World;
class Camera;
class Sound;

class SoundSystem : public System
{
public:
    SoundSystem();

    virtual void beginPlay() override;
    virtual void tick() override;

    static void playSound(Sound* sound);
    static void pauseSound(Sound* sound);
    static void stopSound(Sound* sound);
};

#endif // SOUNDSYSTEM_H

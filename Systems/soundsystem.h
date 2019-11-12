#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "system.h"

class World;
class Sound;

class SoundSystem : public System
{
public:
    SoundSystem();

    void beginPlay() override;
    void tick(float deltaTime) override;

    static void playSound(Sound* sound);
    static void pauseSound(Sound* sound);
    static void stopSound(Sound* sound);
};

#endif // SOUNDSYSTEM_H

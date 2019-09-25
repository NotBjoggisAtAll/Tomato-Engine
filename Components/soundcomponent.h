#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "soundsource.h"
struct Sound
{
    Sound(){}
    Sound(SoundSource* Sound) : audio(Sound){}
    SoundSource* audio{};
};

#endif // SOUNDCOMPONENT_H

#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "component.h"
#include "soundsource.h"
struct SoundComponent : public Component
{
    SoundComponent(){}
    ComponentType Type = ComponentType::Sound;
    SoundSource Sound{};
};

#endif // SOUNDCOMPONENT_H

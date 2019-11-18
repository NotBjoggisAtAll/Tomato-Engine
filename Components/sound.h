#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "component.h"

class SoundSource;

struct Sound : public Component
{
    Sound() = default;
    ~Sound() override;
    Sound(SoundSource* Sound);
    Sound(QJsonObject Json);

    SoundSource* audio_ = nullptr;

    QJsonObject toJson() override;
    virtual void fromJson(QJsonObject Json) override;
};

#endif // SOUNDCOMPONENT_H

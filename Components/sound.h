#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

class SoundSource;
class QJsonObject;

struct Sound
{
    Sound() = default;
    Sound(SoundSource* Sound);
    Sound(QJsonObject JSON);

    SoundSource* audio_{};

    QJsonObject toJson();
};

#endif // SOUNDCOMPONENT_H

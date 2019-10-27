#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "soundsource.h"
#include <QJsonObject>
#include "constants.h"

struct Sound
{
    Sound() = default;
    Sound(SoundSource* Sound) : audio(Sound){}
    SoundSource* audio{};

    Sound(QJsonObject JSON)
    {
        std::string File = gsl::soundFilePath + JSON.take("filepath").toString().toStdString();
        bool Loop = JSON.take("loop").toBool();
        float Gain = static_cast<float>(JSON.take("gain").toDouble());

        audio = new SoundSource(File,Loop,Gain);
    }

    QJsonObject toJSON()
    {
        QJsonObject Object;
        Object.insert("filepath", QString::fromStdString(audio->mName));
        Object.insert("loop", audio->bLoop);
        Object.insert("gain", static_cast<double>(audio->mGain));
        return Object;
    }
};

#endif // SOUNDCOMPONENT_H

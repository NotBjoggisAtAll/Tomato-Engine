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
        std::string File = gsl::soundFilePath + JSON.take("File").toString().toStdString();
        bool Loop = JSON.take("Loop").toBool();
        float Gain = static_cast<float>(JSON.take("Gain").toDouble());

        audio = new SoundSource(File,Loop,Gain);
    }

    QJsonObject toJSON()
    {
        QJsonObject Object;
        Object.insert("File", QString::fromStdString(audio->mName));
        Object.insert("Loop", audio->bLoop);
        Object.insert("Gain", static_cast<double>(audio->mGain));
        return Object;
    }
};

#endif // SOUNDCOMPONENT_H

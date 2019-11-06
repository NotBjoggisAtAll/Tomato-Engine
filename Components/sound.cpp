#include "sound.h"
#include "soundsource.h"
#include "constants.h"
#include <QJsonObject>

Sound::Sound(SoundSource *Sound) : audio_(Sound){}

Sound::Sound(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Sound::toJson()
{
    QJsonObject Object;
    Object.insert("filepath", QString::fromStdString(audio_->mName));
    Object.insert("loop", audio_->bLoop);
    Object.insert("gain", static_cast<double>(audio_->mGain));
    return Object;
}

void Sound::fromJson(QJsonObject Json)
{
    std::string File = gsl::soundFilePath + Json.take("filepath").toString().toStdString();
    bool Loop = Json.take("loop").toBool();
    float Gain = static_cast<float>(Json.take("gain").toDouble());

    audio_ = new SoundSource(File,Loop,Gain);
}

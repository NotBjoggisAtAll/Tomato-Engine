#include "sound.h"
#include "soundsource.h"
#include <QJsonObject>
#include "Managers/soundmanager.h"

Sound::Sound(std::shared_ptr<SoundSource> Sound) : audio_(Sound){}

Sound::Sound(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Sound::toJson()
{
    QJsonObject object;
    object.insert("name", QString::fromStdString(audio_->name_));
    object.insert("filepath", QString::fromStdString(audio_->file_));
    object.insert("loop", audio_->bLoop_);
    object.insert("gain", static_cast<double>(audio_->gain_));
    return object;
}

void Sound::fromJson(QJsonObject Json)
{
    if(!Json.contains("loop")) return;

    std::string name = Json.take("name").toString().toStdString();
    std::string file = Json.take("filepath").toString().toStdString();
    bool loop = Json.take("loop").toBool();
    float gain = static_cast<float>(Json.take("gain").toDouble());

    audio_ = SoundManager::instance()->createSource(name,file,loop,gain);
}

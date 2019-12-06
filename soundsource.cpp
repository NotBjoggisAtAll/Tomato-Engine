#include "soundsource.h"
#include "Handlers/wavfilehandler.h"
#include <sstream>
#include "constants.h"
#include <iostream>

SoundSource::SoundSource(std::string name, std::string file, bool loop, float gain) :
    name_(name),
    file_(file),
    bLoop_(loop),
    gain_(gain),
    source_(0),
    buffer_(0),
    position_(0.0f, 0.0f, 0.0f),
    velocity_(0.0f, 0.0f, 0.0f)
{
    alGetError();
    alGenBuffers(1, &buffer_);
    checkError("alGenBuffers");
    alGenSources(1, &source_);
    checkError("alGenSources");
    alSourcef(source_, AL_PITCH, 1.0f);
    alSourcef(source_, AL_GAIN, gain);

    ALfloat temp[3] = {position_.x, position_.y, position_.z};
    alSourcefv(source_, AL_POSITION, temp);
    ALfloat temp2[3] = {velocity_.x, velocity_.y, velocity_.z};
    alSourcefv(source_, AL_VELOCITY, temp2);

    alSourcei(source_, AL_LOOPING, loop);

    loadWave(file);
}
SoundSource::~SoundSource()
{
    std::cout << "Destroying SoundSource " + name_;
    stop();
    alGetError();
    alSourcei(source_, AL_BUFFER, 0);
    checkError("alSourcei");
    alDeleteSources(1, &source_);
    checkError("alDeleteSources");
    alDeleteBuffers(1, &buffer_);
    checkError("alDeleteBuffers");
}

bool SoundSource::loadWave(std::string filePath)
{
    std::cout << "Loading wave file!\n";
    ALuint frequency{};
    ALenum format{};
    wave_t* waveData = new wave_t();
    if (!WavFileHandler::loadWave(gsl::soundFilePath + filePath, waveData))
    {
        std::cout << "Error loading wave file!\n";
        return false; // error loading wave file data
    }

    frequency = waveData->sampleRate;

    switch (waveData->bitsPerSample)
    {
    case 8:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO8;
            std::cout << "Format: 8bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO8;
            std::cout << "Format: 8bit Stereo\n";
            break;
        default: break;
        }
        break;
    case 16:
        switch (waveData->channels)
        {
        case 1: format = AL_FORMAT_MONO16;
            std::cout << "Format: 16bit Mono\n";
            break;
        case 2: format = AL_FORMAT_STEREO16;
            std::cout << "Format: 16bit Stereo\n";
            break;
        default: break;
        }
        break;
    default: break;
    }

    if (waveData->buffer == nullptr)
    {
        std::cout << "NO WAVE DATA!\n";
    }

    std::ostringstream i2s;
    i2s << waveData->dataSize;
    std::cout << "DataSize: " << i2s.str() << " bytes\n";

    alGetError();
    alBufferData(buffer_, format, waveData->buffer, waveData->dataSize, frequency);
    checkError("alBufferData");
    alSourcei(source_, AL_BUFFER, buffer_);
    checkError("alSourcei (loadWave)");

    std::cout << "Loading complete!\n";
    if (waveData->buffer) delete waveData->buffer;
    if (waveData) delete waveData;
    return true;
}

void SoundSource::play()
{
    qDebug() << QString::fromStdString(name_) + ": Playing!";
    alSourcePlay(source_);
}
void SoundSource::pause()
{
    qDebug() << QString::fromStdString(name_) + ": Paused!";
    alSourcePause(source_);
}
void SoundSource::stop()
{
    qDebug() << QString::fromStdString(name_) + ": Stopped!";
    alSourceStop(source_);
}

bool SoundSource::isPlaying()
{
    ALenum state;
    alGetSourcei(source_, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}

void SoundSource::setPosition(gsl::Vector3D newPos)
{
    position_ = newPos;
    alSourcefv(source_, AL_POSITION, position_.xP());
}
void SoundSource::setVelocity(gsl::Vector3D newVel)
{
    velocity_ = newVel;
    ALfloat temp[3] = {velocity_.x, velocity_.y, velocity_.z};
    alSourcefv(source_, AL_VELOCITY, temp);
}

void SoundSource::setLooping(bool loop)
{
    bLoop_ = loop;
    alSourcei(source_, AL_LOOPING, loop);

}

void SoundSource::setGain(float gain)
{
    gain_ = gain;
    alSourcef(source_, AL_GAIN, gain);
}

bool SoundSource::checkError(std::string name)
{
    switch (alGetError())
    {
    case AL_NO_ERROR:
        break;
    case AL_INVALID_NAME:
        std::cout << "OpenAL Error: "+name+": Invalid name!\n";
        return false;
    case AL_INVALID_ENUM:
        std::cout << "OpenAL Error: "+name+": Invalid enum!\n";
        return false;
    case AL_INVALID_VALUE:
        std::cout << "OpenAL Error: "+name+": Invalid value!\n";
        return false;
    case AL_INVALID_OPERATION:
        std::cout << "OpenAL Error: "+name+": Invalid operation!\n";
        return false;
    case AL_OUT_OF_MEMORY:
        std::cout << "OpenAL Error: "+name+": Out of memory!\n";
        return false;
    default: break;
    }
    return true;
}

#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#ifdef _WIN32
#include <al.h>
#include <alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <string>
#include "JBA/vector3d.h"

/// One sound source.
/**
    Contains one source and one buffer.
    Intended to play a single clip.
    Does not support streaming audio (yet).
**/
class SoundSource
{
public:
    SoundSource(){init("caravan_mono.wav",true,1.f);}
    /// Constructor.
    /**
        Takes two arguments, initialises some variables.
        \param The name of the sound source. Not used.
        \param A boolean to check if sound should loop.
    **/
    SoundSource(std::string name, bool loop = false, float gain = 1.0);
    ~SoundSource();

    /// Plays the sound source from the current position.
    void play();
    /// Pauses the sound source at the current position.
    void pause();
    /// Stops the sound source and rewinds to start.
    void stop();

    /// Checks if the song is playing
    bool isPlaying();

    /// Loads one given WAVE file.
    /**
        Calls the wave loader from the FileHandler class, parses the wave data and buffers it.
        \param The file path relative to the Assets/Sounds folder.
    **/
    bool loadWave(std::string filePath);

    void setPosition(jba::Vector3D newPos);             ///< Sets source position from Vector3.
    jba::Vector3D getPosition() {return mPosition;}     ///< Returns source position as Vector3.
    void setVelocity(jba::Vector3D newVel);             ///< Sets source velocity from Vector3.
    jba::Vector3D getVelocity() {return mVelocity;}     ///< Returns source velocity as Vector3.

    std::string mName;          ///< The name of the sound source (Not used).
    
    void init(std::string name, bool loop, float gain);
private:
    ALuint mSource;             ///< The sound source.
    ALuint mBuffer;             ///< The data buffer.
    jba::Vector3D mPosition{};    ///< Vector containing source position.
    jba::Vector3D mVelocity{};    ///< Vector containing source velocity.
    bool checkError(std::string name);
};

#endif

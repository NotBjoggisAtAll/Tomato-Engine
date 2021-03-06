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
#include "GSL/vector3d.h"

/// One sound source.
/**
    Contains one source and one buffer.
    Intended to play a single clip.
    Does not support streaming audio (yet).
**/
class SoundSource
{
public:
    SoundSource() = default;
    /// Constructor.
    /**
        Takes two arguments, initialises some variables.
        \param The name of the sound source.
        \param A boolean to check if sound should loop.
    **/
    SoundSource(std::string name, std::string file, bool loop = false, float gain = 1.0);
    ~SoundSource();

    /// Plays the sound source from the current position.
    void play();
    /// Pauses the sound source at the current position.
    void pause();
    /// Stops the sound source and rewinds to start.
    void stop();

    /// Checks if the song is playing
    bool isPlaying();

    void setPosition(gsl::Vector3D newPos);             ///< Sets source position from Vector3.
    gsl::Vector3D getPosition() const {return position_;}     ///< Returns source position as Vector3.
    void setVelocity(gsl::Vector3D newVel);             ///< Sets source velocity from Vector3.
    gsl::Vector3D getVelocity() const {return velocity_;}     ///< Returns source velocity as Vector3.

    void setLooping(bool loop);
    void setGain(float gain);

    std::string name_;
    std::string file_;
    bool bLoop_ = false;
    float gain_ = 0.f;
    
private:
    /// Loads one given WAVE file.
    /**
        Calls the wave loader from the FileHandler class, parses the wave data and buffers it.
        \param The file path relative to the Assets/Sounds folder.
    **/
    bool loadWave(std::string filePath);

    ALuint source_;             ///< The sound source.
    ALuint buffer_;             ///< The data buffer.
    gsl::Vector3D position_{};    ///< Vector containing source position.
    gsl::Vector3D velocity_{};    ///< Vector containing source velocity.
    bool checkError(std::string name);
};

#endif

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#ifdef _WIN32
#include <al.h>
#include <alc.h>
#endif
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <string>
#include <vector>
#include "soundsource.h"
#include "GSL/vector3d.h"
#include <memory>

/// Class handling OpenAL setup and management of sound sources.
/**
    Singleton class that creates and destroys sound sources.
**/
class SoundManager
{
public:
    static SoundManager* instance();

    /// Cleans up and shuts down OpenAl.
    void cleanUp();

    /// Creates a new SoundSource with the given parameters.
    /**
        \param The name of the sound.
        \param The source position as gsl::Vector3D.
        \param File path relative to execution directory.
        \param Boolean to see if sound should loop or not.
    **/
    std::shared_ptr<SoundSource> createSource(std::string name, std::string file = "", bool loop = false, float gain = 1.0);
    void updateListener(gsl::Vector3D pos, gsl::Vector3D vel, gsl::Vector3D dir, gsl::Vector3D up);

private:
    SoundManager();                         ///< Private constructor.
   // SoundManager(SoundManager const&);      ///< Private copy constructor.
   // void operator=(SoundManager const&);    ///< Private class assignment operator.
    static SoundManager* instance_;         ///< Singleton instance pointer.
    /// Debug function.
    /**
        Checks for and outputs OpenAL errors.
    **/
    bool checkError();

    ALCdevice* mDevice;                 ///< Pointer to the ALC Device.
    ALCcontext* mContext;               ///< Pointer to the ALC Context.

};

#endif

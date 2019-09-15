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
#include "JBA/vector3d.h"

/// Class handling OpenAL setup and management of sound sources.
/**
    Singleton class that creates and destroys sound sources.
**/
class SoundManager
{
public:
    struct SoundListener
    {
        jba::Vector3D pos;
        jba::Vector3D vel;
        jba::Vector3D dir;
        jba::Vector3D up;
        SoundListener()
        {
            pos = jba::Vector3D(0.0f, 0.0f, 0.0f);
            vel = jba::Vector3D(0.0f, 0.0f, 0.0f);
            dir = jba::Vector3D(0.0f, 0.0f, 1.0f);
            up = jba::Vector3D(0.0f, 1.0f, 0.0f);
            //Could be something like this, if Vector3-class had support support:
            //pos = Vector3::ZERO;
            //vel = Vector3::ZERO;
            //dir = Vector3::UNIT_Z;
            //up = Vector3::UNIT_Y;
        }
    };

    static SoundManager* instance();

    /// Cleans up and shuts down OpenAl.
    void cleanUp();

    /// Creates a new SoundSource with the given parameters.
    /**
        \param The name of the sound. (Not in use.)
        \param The source position as jba::Vector3D.
        \param File path relative to execution directory.
        \param Boolean to see if sound should loop or not.
    **/
    SoundSource *createSource(std::string name, jba::Vector3D pos, std::string filePath = "", bool loop = false, float gain = 1.0);
    void updateListener(jba::Vector3D pos, jba::Vector3D vel, jba::Vector3D dir, jba::Vector3D up);

private:
    SoundManager();                         ///< Private constructor.
   // SoundManager(SoundManager const&);      ///< Private copy constructor.
   // void operator=(SoundManager const&);    ///< Private class assignment operator.
    static SoundManager* mInstance;         ///< Singleton instance pointer.
    /// Debug function.
    /**
        Checks for and outputs OpenAL errors.
    **/
    bool checkError();

    ALCdevice* mDevice;                 ///< Pointer to the ALC Device.
    ALCcontext* mContext;               ///< Pointer to the ALC Context.

    SoundListener mListener;               ///< The listener data structure. (Temporary)
};

#endif

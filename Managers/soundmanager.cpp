#include "soundmanager.h"
#include "Handlers/wavfilehandler.h"
#include <QDebug>
#include <constants.h>

SoundManager* SoundManager::mInstance = nullptr;

SoundManager::SoundManager() :
    mDevice(nullptr),
    mContext(nullptr)
{
    qDebug() << "Intializing OpenAL!\n";
    mDevice = alcOpenDevice(nullptr);
    if (mDevice)
    {
        mContext = alcCreateContext(mDevice, nullptr);
        alcMakeContextCurrent(mContext);
    }

    // Generate buffers
    alGetError();

    if (!mDevice)
    {
        qDebug() << "Device not made!\n";
    }
    else
        qDebug() << "Intialization complete!\n";
}

SoundManager *SoundManager::instance()         ///< Get pointer to singleton instance.
{
    if (!mInstance)
        mInstance = new SoundManager();
    return mInstance;
}

void SoundManager::cleanUp()
{
    mContext = alcGetCurrentContext();
    mDevice = alcGetContextsDevice(mContext);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(mContext);
    alcCloseDevice(mDevice);
}

bool SoundManager::checkError()
{
    switch (alGetError())
    {
    case AL_NO_ERROR:
        break;
    case AL_INVALID_NAME:
        qDebug() << "Invalid name!\n";
        return false;
    case AL_INVALID_ENUM:
        qDebug() << "Invalid enum!\n";
        return false;
    case AL_INVALID_VALUE:
        qDebug() << "Invalid value!\n";
        return false;
    case AL_INVALID_OPERATION:
        qDebug() << "Invalid operation!\n";
        return false;
    case AL_OUT_OF_MEMORY:
        qDebug() << "Out of memory!\n";
        return false;
    default: break;
    }
    return true;
}

SoundSource* SoundManager::createSource(std::string name, jba::Vector3D pos, std::string filePath, bool loop, float gain)
{

    SoundSource* tempPtr = new SoundSource(name, loop, gain);
    tempPtr->setPosition(pos);
    if (filePath != "")
    {
        auto folder = gsl::soundFilePath;
        tempPtr->loadWave(folder + filePath);
    }
    return tempPtr;
}

void SoundManager::updateListener(jba::Vector3D pos, jba::Vector3D vel, jba::Vector3D dir, jba::Vector3D up)
{
    ALfloat posVec[3];
    ALfloat velVec[3];
    ALfloat headVec[6];
    posVec[0] = pos.x();
    posVec[1] = pos.y();
    posVec[2] = pos.z();
    velVec[0] = vel.x();
    velVec[1] = vel.y();
    velVec[2] = vel.z();
    headVec[0] = dir.x();
    headVec[1] = dir.y();
    headVec[2] = dir.z();
    headVec[3] = up.x();
    headVec[4] = up.y();
    headVec[5] = up.z();
    alListenerfv(AL_POSITION, posVec);
    alListenerfv(AL_VELOCITY, velVec);
    alListenerfv(AL_ORIENTATION, headVec);
}

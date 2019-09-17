#include "soundsystem.h"
#include "resourcemanager.h"
#include "camera.h"
#include "Managers/soundmanager.h"

/**
 * TODO
 * Take a look at the soundmanager and the sound system?
 * Maybe I could merge them together?
 */


SoundSystem::SoundSystem()
{
    Factory = ResourceManager::instance();
    SoundManager::instance();
}

// TODO Need to find a way to not send in the camera
void SoundSystem::update(Camera* currCamera)
{
    // Updates listener location
    jba::Vector3D cameraPos{currCamera->position().getX(),
                currCamera->position().getY(),
                currCamera->position().getZ()};

    jba::Vector3D cameraForward{currCamera->forward().getX(),
                currCamera->forward().getY(),
                currCamera->forward().getZ()};

    jba::Vector3D cameraUp{currCamera->up().getX(),
                currCamera->up().getY(),
                currCamera->up().getZ()};

    SoundManager::instance()->updateListener(cameraPos,
                                             {},
                                             cameraForward,
                                             cameraUp);

    //Updates sound location
    for(auto& Sound : Factory->mSoundComponents)
    {

        auto Transform = Factory->getTransformComponent(Sound.EntityID);

        //TODO Fixup gsl::Transform.mMatrix to a jba::Matrix4x4
        jba::Vector3D pos{Transform->mMatrix.getPosition().getX(),
                    Transform->mMatrix.getPosition().getY(),
                    Transform->mMatrix.getPosition().getZ()};
        Sound.Sound.setPosition(pos);

        //For now loops all the sounds - This is going to change
        if(!Sound.Sound.isPlaying())
        {
            Sound.Sound.play();
        }
    }

}

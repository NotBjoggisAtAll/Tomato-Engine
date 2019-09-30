#include "soundsystem.h"
#include "camera.h"
#include "Managers/soundmanager.h"
#include "World.h"
#include "Components/allcomponents.h"
/**
 * TODO
 * Take a look at the soundmanager and the sound system?
 * Maybe I could merge them together?
 */

SoundSystem::SoundSystem()
{
    SoundManager::instance();
    world = getWorld();
}

// TODO Need to find a way to not send in the camera
void SoundSystem::update(Camera* currCamera)
{
    // Updates listener location
    gsl::Vector3D cameraPos{currCamera->position().getX(),
                currCamera->position().getY(),
                currCamera->position().getZ()};

    gsl::Vector3D cameraForward{currCamera->forward().getX(),
                currCamera->forward().getY(),
                currCamera->forward().getZ()};

    gsl::Vector3D cameraUp{currCamera->up().getX(),
                currCamera->up().getY(),
                currCamera->up().getZ()};

    SoundManager::instance()->updateListener(cameraPos,
    {},
                                             cameraForward,
                                             cameraUp);

    for(auto const& entity : mEntities)
    {
        auto sound = world->getComponent<Sound>(entity).value();
        auto transform = world->getComponent<Transform>(entity).value();

        sound->audio->setPosition(transform->position);

        //For now loops all the sounds - This is going to change
        if(!sound->audio->isPlaying())
        {
            sound->audio->play();
        }
    }
}

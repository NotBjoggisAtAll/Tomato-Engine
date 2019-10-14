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
    if(!world->bGameRunning)
    {
        for(auto const& entity : mEntities)
        {
            auto sound = world->getComponent<Sound>(entity).value();
            sound->audio->stop();
        }
        return;
    }

    SoundManager::instance()->updateListener(currCamera->position(),
    {},
                                             currCamera->forward(),
                                             currCamera->up());

    for(auto const& entity : mEntities)
    {
        auto sound = world->getComponent<Sound>(entity).value();
        auto transform = world->getComponent<Transform>(entity).value();

        sound->audio->setPosition(transform->position);

        //For now loops all the sounds - This is going to change
        if(!sound->audio->isPlaying())
            sound->audio->play();
    }
}

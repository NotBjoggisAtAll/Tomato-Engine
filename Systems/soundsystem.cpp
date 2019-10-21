#include "soundsystem.h"
#include "camera.h"
#include "Managers/soundmanager.h"
#include "World.h"
#include "Components/soundcomponent.h"
#include "Components/transformcomponent.h"

/**
 * TODO
 * Take a look at the soundmanager and the sound system?
 * Maybe I could merge them together?
 */

SoundSystem::SoundSystem()
{
    SoundManager::instance();
}

void SoundSystem::beginPlay()
{
    for(auto const& entity : mEntities)
    {
        auto sound = getWorld()->getComponent<Sound>(entity).value();
        sound->audio->stop();
    }
}

void SoundSystem::tick()
{
    Camera* currCamera = getWorld()->getCurrentCamera();
    SoundManager::instance()->updateListener(currCamera->position(),
                                             {},
                                             currCamera->forward(),
                                             currCamera->up());

    for(auto const& entity : mEntities)
    {
        auto sound = getWorld()->getComponent<Sound>(entity).value();
        auto transform = getWorld()->getComponent<Transform>(entity).value();
        sound->audio->setPosition(transform->position);
    }
}

void SoundSystem::playSound(Sound *sound)
{
    if(!sound->audio->isPlaying())
        sound->audio->play();
}

void SoundSystem::pauseSound(Sound *sound)
{
    if(sound->audio->isPlaying())
        sound->audio->pause();
}

void SoundSystem::stopSound(Sound *sound)
{
        sound->audio->stop();
}

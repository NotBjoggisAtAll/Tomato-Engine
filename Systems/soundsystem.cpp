#include "soundsystem.h"
#include "Managers/soundmanager.h"
#include "world.h"
#include "Components/sound.h"
#include "Components/transform.h"
#include "Components/camera.h"

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
    for(auto const& entity : entities_)
    {
        auto sound = getWorld()->getComponent<Sound>(entity).value();
        sound->audio_->stop();
    }
}

void SoundSystem::tick(float deltaTime)
{
    auto currCamera = getWorld()->getComponent<Camera>(getWorld()->getCurrentCamera()).value_or(nullptr);
    auto cameraTransform = getWorld()->getComponent<Transform>(getWorld()->getCurrentCamera()).value_or(nullptr);

    if(!currCamera || !cameraTransform)
        return;

    SoundManager::instance()->updateListener(cameraTransform->position_,
                                             {},
                                             currCamera->forward_,
                                             currCamera->up_);

    for(auto const& entity : entities_)
    {
        auto sound = getWorld()->getComponent<Sound>(entity).value();
        auto transform = getWorld()->getComponent<Transform>(entity).value();
        sound->audio_->setPosition(transform->position_);
    }
}

void SoundSystem::playSound(Sound *sound)
{
    if(!sound->audio_->isPlaying())
        sound->audio_->play();
}

void SoundSystem::pauseSound(Sound *sound)
{
    if(sound->audio_->isPlaying())
        sound->audio_->pause();
}

void SoundSystem::stopSound(Sound *sound)
{
        sound->audio_->stop();
}

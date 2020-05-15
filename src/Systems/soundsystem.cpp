#include "soundsystem.h"
#include "Managers/soundmanager.h"
#include "world.h"
#include "Components/sound.h"
#include "Components/transform.h"
#include "Components/camera.h"

void SoundSystem::beginPlay()
{
    for(auto const& entity : entities_)
    {
        auto sound = getWorld()->getComponent<Sound>(entity).value();
        sound->audio_->stop();
    }
}

void SoundSystem::tick(float /*deltaTime*/)
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
        if(!sound->audio_)
            continue;

        auto transform = getWorld()->getComponent<Transform>(entity).value();
        sound->audio_->setPosition(transform->position_);
    }
}

void SoundSystem::endPlay()
{
    for(auto const& entity : entities_)
    {
        auto sound = getWorld()->getComponent<Sound>(entity).value();
        sound->audio_->stop();
    }
}

void SoundSystem::playSound(Sound *sound)
{
    if(!sound->audio_)
        return;
    if(!sound->audio_->isPlaying())
        sound->audio_->play();
}

void SoundSystem::pauseSound(Sound *sound)
{
    if(!sound->audio_)
        return;
    if(sound->audio_->isPlaying())
        sound->audio_->pause();
}

void SoundSystem::stopSound(Sound *sound)
{
    if(!sound->audio_)
        return;
    sound->audio_->stop();
}


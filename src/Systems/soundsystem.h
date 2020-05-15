#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "system.h"

struct Sound;

/**
 * The SoundSystem  is responsible to play, pause and stop sounds.
 * It also updates the listener's position (camera position) and the sound component's position.
 */
struct SoundSystem : public System
{
    /**
     * Default constructor.
     */
    SoundSystem() = default;

    /**
     * BeginPlay runs when the the actual game starts.
     * Stops all sounds playing before the game starts.
     * (Eg. if you're testing sounds in the editor you want them to stop before you play)
     */
    void beginPlay() override;

    /**
     * Tick runs every frame.
     * Updates the Listener's position and the Sound component's position.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    void tick(float deltaTime) override;

    /**
     * EndPlay runs when the games end and goes back to the editor.
     * Stops all sounds playing before the game stops.
     */
    void endPlay() override;

    /**
     * Plays the sound given.
     * @param sound - Sound.
     */
    static void playSound(Sound* sound);

    /**
     * Pauses the sound given.
     * @param sound - Sound.
     */
    static void pauseSound(Sound* sound);

    /**
     * Stops the sound given.
     * @param sound - Sound.
     */
    static void stopSound(Sound* sound);

};

#endif // SOUNDSYSTEM_H

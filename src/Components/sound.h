#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "component.h"
#include <memory>

class SoundSource;

/**
 * The Sound component holds a SoundSource which is the audio loaded from a file.
 */
struct Sound : public Component
{
    /**
     * Default constructor.
     */
    Sound() = default;

    /**
     * A constructor taking in a soundsource.
     * Use the SoundManager to create a SoundSource.
     * @param Sound - SoundSource.
     * @param playOnSpawn - bool. True if the sound should play when this is created.
     */
    Sound(std::shared_ptr<SoundSource> Sound, bool playOnSpawn = false);
    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Sound component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Sound(QJsonObject Json);

    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    QJsonObject toJson() override;

    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    void fromJson(QJsonObject Json) override;

    /// A pointer to the SoundSource.
    std::shared_ptr<SoundSource> audio_;
};

#endif // SOUNDCOMPONENT_H

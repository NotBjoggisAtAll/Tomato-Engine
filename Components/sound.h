#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "component.h"

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
     */
    Sound(SoundSource* Sound);
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
    SoundSource* audio_ = nullptr;
};

#endif // SOUNDCOMPONENT_H

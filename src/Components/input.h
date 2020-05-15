#ifndef INPUT_H
#define INPUT_H

#include "component.h"

/**
 * The Input component is used to control an Entity. If a Entity have this Component it can be controlled with WASD.
 */
struct Input : public Component
{
    /**
     * Default constructor.
     */
    Input() = default;
    /**
     * A constructor taking in a bool.
     * @param isControlable - bool. If this is true the Entity is controllable.
     */
    Input(bool isControlable);

    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Input component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Input(QJsonObject Json);

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

    /// Used to check if the Entity is controllable.
    bool isControllable = true;
};

#endif // INPUT_H

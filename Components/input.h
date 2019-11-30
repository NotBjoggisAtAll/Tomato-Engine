#ifndef INPUT_H
#define INPUT_H

#include "component.h"

/**
 * The Input component is used to control an entity. If a entity have this component it can be controlled with WASD.
 */
struct Input : public Component
{
    /**
     * Default constructor.
     */
    Input() = default;
    /**
     * A constructor taking in a bool.
     * @param isControlable - bool. If this is true the player is controllable.
     */
    Input(bool isControlable);
    /**
     *
     * @param Json
     */
    Input(QJsonObject Json);
    QJsonObject toJson() override;
    void fromJson(QJsonObject Json) override;

    bool isControllable = true;
};

#endif // INPUT_H

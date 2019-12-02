#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Components/component.h"
#include "GSL/vector3d.h"
#include <vector>

/**
 * The Projectile component is used to make object move like a Projectile.
 * It stores values like speed, lifetime and direction. Also has a std::vector with different Npc positions.
 */
struct Projectile : public Component
{
    /**
     * Default constructor.
     */
    Projectile() = default;

    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Projectile component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Projectile(QJsonObject Json);

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

    /// The direction the projectile is going. Set by a ProjectileSystem.
    gsl::Vector3D direction_ = gsl::Vector3D(0);

    /// The projectile's speed.
    float speed_ = 5;

    /// The projectile's lifetime. The Entity is destroyed when the Projectile has exceeded its lifetime or if it hits something.
    float lifetime_ = .5f;

    /// Used to set the Projectile's direction. Set to true when the Projectile gets a valid direction.
    bool routeCalculated = false;

    /// A vector with the the nearest Npc positions. Used to calculate what to shoot at.
    std::vector<gsl::Vector3D> npcPositions_;

};

#endif // PROJECTILE_H

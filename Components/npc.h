#ifndef NPC_H
#define NPC_H

#include "component.h"

class BSplineCurve;

/**
 * The different states the Npc can have.
 */
enum class NPCstates {SLEEP = 0, PATROL};

/**
 * The different events the Npc can trigger.
 */
enum class NPCevents {ENDPOINT_ARRIVED = 0, ITEM_TAKEN, PLAYER_DETECTED, OBSTACLE_DETECTED};

/**
 * The Npc component is used to move objects along a BSplineCurve.
 * It has events and states which decide what the Npc will do. This is controlled by a NpcSystem.
 */
struct Npc : public Component
{
    /**
     * Default constructor.
     */
    Npc() = default;
    /**
     * A constructor taking in a pointer to a BSplineCurve.
     * @param Curve - BSplineCurve. Get the BSplineCurve from a BSpline component.
     */
    Npc(BSplineCurve* Curve);

    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Npc component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Npc(QJsonObject Json);

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

    /// A pointer to a BSplineCurve. Get the BSplineCurve from a BSpline component.
    BSplineCurve* bSplineCurve = nullptr;

    /// Stores the current event the Npc has. Used in a NpcSystem.
    NPCevents event_;

    /// Stores the current state the Npc has. Used in a NpcSystem.
    NPCstates state_;

    /// The speed the Npc moves along a BSplineCurve.
    float speed_ = 0.1f;

    /// The current location the Npc has on a BSplineCurve. Goes from 0 to 1.
    float currentT_ = 0;

};

#endif // NPC_H

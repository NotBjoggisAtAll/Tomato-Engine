#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "component.h"
#include "types.h"
#include <vector>

/**
 * The EntityData contains information like the Entity's name and parent/child relationship.
 */
struct EntityData : public Component
{

    /**
      * Default Constructor.
      */
    EntityData() = default;

    /**
     * Constructor that takes in a Name for the Entity.
     * @param Name - std::string
     */
    EntityData(std::string Name);

    /**
     * Constructor that takes in a QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise a default EntityData is made.
     * @param Json - QJsonObject
     */
    EntityData(QJsonObject Json);

    /**
     * Makes a QJsonObject containing the EntityData data.
     * @return Returns a QJsonObject
     */
    QJsonObject toJson();

    /**
     * Override the data in the EntityData with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    void fromJson(QJsonObject Json);

    ///Name. Only used in the UI.
    std::string name_ = "Entity";
    ///Parent. The Entity id of the parent. If no parent the value is -1.
    Entity parent_{-1};
    ///Children. A std::vector containing all children of this Entity.
    std::vector<Entity> children_;

};

#endif // ENTITYDATA_H

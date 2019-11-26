#ifndef COMPONENT_H
#define COMPONENT_H

#include <QJsonObject>

/**
 * A interface for other components.
 */
struct Component
{
    virtual ~Component();

    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    virtual QJsonObject toJson() = 0;

    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    virtual void fromJson(QJsonObject Json) = 0;

};

#endif // COMPONENT_H

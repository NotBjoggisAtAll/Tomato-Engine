#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "component.h"
#include <QJSEngine>
#include <QString>

/**
 * The Script component holds a QJSEngine which is used to talk/read/write to a JavaScript file.
 */
struct Script : public Component
{
    /**
     * Default constructor.
     */
    Script() = default;

    /**
     * A constructor taking in a QString which is the JavaScript filepath.
     * Assumes the location is Assets/Scripts. Creates a QJsEngine when constructed.
     * @param fileName - QString.
     */
    Script(QString fileName);

    /**
     * A constructor taking in a QJsonObject.
     * @param Json - QJsonObject. Creates a Script component with the data in the QJsonObject. If the QJsonObject is not valid the component is constructed with default values.
     */
    Script(QJsonObject Json);

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

    /// The JavaScript filepath. Assumes the location is Assets/Scripts.
    QString file_ = "";

    /// A pointer to the QJSEngine. The engine is used to talk,read,write data to JavaScript.
    QJSEngine* engine_ = nullptr;
};

#endif // SCRIPTCOMPONENT_H

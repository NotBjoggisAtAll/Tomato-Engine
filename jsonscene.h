#ifndef JSONSCENE_H
#define JSONSCENE_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include "types.h"

/**
 * A wrapper class used when you want to save a scene.
 * When saving a scene all entities are added to the sceneObject variable in this class.
 * The class handles the saving to file.
 */
class JsonScene
{
public:
    /**
     * Default constructor.
     * @param SceneName - The SceneName. The name is added to the JSON file.
     */
    JsonScene(QString SceneName);

    /**
     * Makes a file where at the absolutefilePath and adds all entities in the world.
     * @param absolutefilePath - QString.
     * @param overwrite - boolean. True if you want to override the exiting file. False by default.
     */
    void makeFile(QString absolutefilePath, bool overwrite = false);

    /**
     * Makes a temporary file in the build folder.
     * This is only used when starting/stopping the game. To save and reset the level.
     * @param sceneName - QString.
     */
    void makeTempFile(QString sceneName);

    /**
     * Adds a entity to the scene.
     * @param entity - Entity.
     */
    void addObject(Entity entity);
private:

    /// The final JSON object containing all the information to save to the file.
    QJsonObject sceneObject_ = QJsonObject();

    /// An array with all entities that should be added to the file.
    QJsonArray entities_ = QJsonArray();
};
#endif // JSONSCENE_H

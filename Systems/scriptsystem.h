#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "Systems/system.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJSValue>
#include <vector>
#include <QJsonArray>

class JSTimer;
struct Script;
class QJSEngine;

/**
 * The ScriptSystem reads and executes JS files.
 * The class contains the normal system functions, but also
 * alot of public slots.
 * All the functions under public slots are functions that are available in JavaScript.
 */
class ScriptSystem : public System
{
    Q_OBJECT
public:

    /**
     * Default constructor.
     */
    ScriptSystem() = default;

    /**
     * BeginPlay runs when the the actual game starts.
     * Finds all Script components and run the function componentAdded() to evaluate and load the JavaScript file.
     */
    void beginPlay() override;

    /**
     * Tick runs every frame.
     * Calls all the tick functions in JavaScript.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    void tick(float deltaTime) override;

    /**
     * EndPlay runs when the games end and goes back to the editor.
     * Calls all the endPlay functions in JavaScript.
     * And deletes all the JSTimers.
     */
    void endPlay() override;

    /**
     * Called by beginPlay or when a script component is added while the game is playing.
     * Loads and evaulates the script and runs the beginPlay in JavaScript.
     * @param script - Script.
     * @param entity - Entity.
     */
    void componentAdded(Script* script, Entity entity);

public slots:
    /**
     * JavaScript function.
     * Used to create a entity in script.
     * @return the Entity ID.
     */
    int createEntity();

    /**
     * JavaScript function.
     * Used to spawn an enemy with script.
     * Spawns a enemy and attaches it to a BSpline.
     * @param owner - int. Assumes the owner contains a BSpline component.
     */
    void spawnEnemy(int owner);

    /**
     * JavaScript function.
     * Used to get a component with a string reference.
     * Atm "Transform" is the only one available.
     * @param name - The Component name (Eg. "Transform").
     * @param entity - The owning entity of the component.
     * @return The component as a JSON Object.
     */
    QJsonValue getComponent(QString name, int entity);

    /**
     * JavaScript function.
     * Used to get all Npc locations in the world.
     * @return A JavaScript array with all the positions.
     */
    QJsonValue getAllNpcLocations();

    /**
     * JavaScript function.
     * @param owner - The owning Entity that want to call this function.
     * @param npcs - All npcs inside the range. Got from JavaScript.
     */
    void shoot(int owner, QJsonArray npcs);
private:

    /**
     * Used to call a JavaScript function. (Eg. "Tick")
     * @param script - The script you want to call a function on.
     * @param function - The function you want to call.
     */
    void call(Script *script, QString function);

    /**
     * Used to load and evaluate a JavaScript file.
     * @param script - The JavaScript file you want to evaluate.
     */
    void load(Script *script);

    /// A vector with JSTimers. Created when needed and deleted at endPlay.
    std::vector<JSTimer*> timers_;
};

#endif // SCRIPTSYSTEM_H

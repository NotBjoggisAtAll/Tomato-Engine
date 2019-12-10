#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include "types.h"
#include <QObject>

/**
 * The System is a base class for all Systems in ECS.
 * All systems needs to derive from this class.
 * It contains a std::set with the Entities the System is responsible for.
 */
class System : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor.
     */
    System() = default;

    /**
     * Default deconstructor.
     */
    virtual ~System() = default;

    /**
     * BeginPlay runs when the the actual game starts.
     */
    virtual void beginPlay(){}

    /**
     * Tick runs every frame.
     * Some systems only need to tick while the game is running. See the App tick function for more details.
     * @param deltaTime - The time since last frame. Usually at 16 ms.
     */
    virtual void tick(float deltaTime){}

    /**
     * EndPlay runs when the games end and goes back to the editor.
     */
    virtual void endPlay(){}

    /// The set only contains entities that the System is responsible for. The SystemManager is responsible to update this set.
    std::set<Entity> entities_;
};

#endif // SYSTEM_H

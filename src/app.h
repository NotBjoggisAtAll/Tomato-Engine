#ifndef APP_H
#define APP_H

#include <memory>
#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

#include "types.h"
#include "mainwindow.h"
#include "GSL/vector3d.h"
#include "GSL/vector2d.h"

class RenderWindow;
class EventHandler;

/** \mainpage Welcome to the Tomato Engine documentation!
 * This engine was created as a project in Game Engine Architecture at the Inland Norway University of Applied Sciences.
 * @author <a href="https://github.com/NotBjoggisAtAll">NotBjoggisAtAll</a> on GitHub.
 * @date Fall of 2019.*/

/**
 * The App class is the main class that connects everything together.
 * It's here you create and connect everything together.
 * The App is creating the MainWindow which is the editor itself.
 * App contains the actual gameloop while the program is running.
 */
class App : public QObject
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * The constructor registers and sets up all the components and systems.
     * It also creates the MainWindow and connect a bunch of signals and slots together.
     * The constructor starts the gameloop aswell.
     */
    App();

    /**
     * Default deconstructor.
     * Cleans up SoundManager.
     */
    ~App();

private slots:
    /**
     * postInit is run after the MainWindow and the RenderWindow is created and finished initalizing.
     * Here you typically creates entities to show in the world, now that everything is set up correctly.
     */
    void postInit();

    /**
     * Tick runs every frame (16ms).
     * It runs all the different systems tick function in a specific order to make it work properly.
     */
    void tick();

    /**
     * playGame is called from the MainWindow when the user pressed the Playbutton.
     * It runs the beginPlay function in different systems.
     */
    void playGame();

    /**
     * stopGame is called from the MainWindow when the user pressed the Stopbutton.
     * It runs the endPlay function in different systems.
     */
    void stopGame();

    /**
     * Deletes all entities and makes a new clean scene.
     */
    void newScene();

    /**
     * Clears the scene and makes a prompt of loading a new one.
     * Opens a filedialog so the user can choose a JSON file to open.
     */
    void loadScene();

    /**
     * Saves the scene to a JSON file.
     * Opens a filedialog so the user can choose a JSON file to save to.
     */
    void saveScene();

    /**
     * Called when the button Create->Empty Entity is pressed.
     * Creates a new entity, gives it a default name and shows it in the world outliner.
     * @return the Entity created.
     */
    Entity createEntity();

    /**
     * Called when the buttons under the Create menu is pressed (Except Empty Entity).
     * Creates a new entity and gives its components based on what type of object you want to create.
     * @param name - the object name.
     * @param path - the mesh path for the object.
     * @return the Entity created.
     */
    Entity spawnObject(std::string name, std::string path);

    /**
     * Updates all the cameras perspective matrices.
     * Run whenever the RenderWindow is resized.
     * @param aspectRatio - The RenderWindow's aspect ratio.
     */
    void updateCameraPerspectives(float aspectRatio);

    /**
     * Called whenever the user presses the left mouse button.
     * Called from the EventHandler.
     * Mainly used for mousepicking to select object. And when playing the game.
     */
    void mouseLeftClick();

    /**
     * Called when the collision system detects two entities that collided.
     * This function runs custom logic for the game to work.
     * Deletes the projectile and the npc if they hit eachother.
     * @param entity1 - Entity.
     * @param entity2 - Entity.
     */
    void entitiesCollided(Entity entity1, Entity entity2);

private:
    /// A unique pointer to the MainWindow.
    std::unique_ptr<MainWindow> mainWindow_;

    /// A shared pointer to the RenderWindow.
    std::shared_ptr<RenderWindow> renderWindow_;

    /// A shared pointer to the EventHandler.
    std::shared_ptr<EventHandler> eventHandler_;

    /// The tick timer. Makes the tick function run in a loop.
    QTimer tickTimer_;

    /// Stores the current deltaTime.
    float deltaTime_ = 0;

    /// At the beginning of each frame the deltaTime is added to this. Used to print the deltaTime more accurately on the statusbar. Reset when printed.
    float totalDeltaTime_ = 0;

    /// A timer that resets every 100 frames. It's job is to update the statusbar every 100 frame. No need to update it every frame.
    QElapsedTimer frameTimer_;

    /// A timer that holds the current deltaTime. At the beginning of each frame this is reset and its value is set to the deltaTime.
    QElapsedTimer deltaTimer_;

    /// A counter that increases everyframe. Used to display the deltatime more accurately. Reset every time its printed to the statusbar.
    int frameCounter = 0;

    /**
     * Calculates the framerate and prints it to the statusbar.
     */
    void calculateFramerate();

    /**
     * Custom game logic.
     * Called whenever the user plays the game and presses left click.
     * Spawns a tower that shoots at enemies.
     * @param hitPosition - The position the turret is going to spawn.
     */
    void spawnTower(gsl::Vector3D hitPosition);

    /**
     * Registers all the components. Must be called before any component is used.
     */
    void registerComponents();

    /**
     * Registers all the systems. Must be called before any system is used.
     */
    void registerSystems();

    /**
     * Gives all the systems different signatures based on what components they need. Must be called before any system is used.
     */
    void setSystemSignatures();
};

#endif // APP_H

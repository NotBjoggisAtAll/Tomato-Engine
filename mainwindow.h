#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "types.h"
#include <memory>

class QWidget;
class RenderWindow;
class QTreeWidgetItem;

namespace Ui {
class MainWindow;
}

/**
 * The MainWindow is the actual window containing everything.
 * The MainWindow is responsible for showing all the editor widgets.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Setting up default settings for some widgets in the editor.
     * Makes the renderwindow.
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~MainWindow();

    /**
     * Displays all entities in the world outliner.
     */
    void displayEntitiesInOutliner();

    /**
     * Used to add a entity to the outliner.
     * @param entity - Entity.
     */
    void addEntityToOutliner(Entity entity);

    /**
     * Called when App updates the statusbar.
     * @param timePerFrame - float.
     * @param frameCounter - float.
     * @param verticeCounter - int.
     */
    void updateStatusbar(float timePerFrame, float frameCounter, int verticeCounter);

    /**
     * A shared pointer to RenderWindow.
     */
    std::shared_ptr<RenderWindow> renderWindow_ = nullptr;

signals:
    /**
     * Emitted when the play button is pressed.
     */
    void playGame_signal();

    /**
     * Emitted when the stop button is pressed.
     */
    void stopGame_signal();

    /**
     * Emitted when the user spawns a premade object from the editor.
     * @param name - The name of the object.
     * @param path - The path of the object. Used in the ResourceFactory.
     * @return the entity created.
     */
    Entity spawnObject(std::string name, std::string path);

    /**
     * Emitted when the user creates an empty entity.
     * @return the entity created.
     */
    Entity createEntity();

    /**
     * Emitted when the user is pressing the load scene button.
     */
    void loadScene();

    /**
     * Emitted when the user is pressing the new scene button.
     */
    void newScene();

    /**
     * Emitted when the user is pressing the save scene button.
     */
    void saveScene();

public slots:

    /**
     * Updates the component panel when called.
     * Displays all component widgets that the entity has.
     * @param entity - Entity.
     */
    void updateRightPanel(Entity entity);

private slots:

    /**
     * Called when the user presses the toggle wireframe button.
     */
    void on_actionToggle_Wireframe_triggered();

    /**
     * Called when the user presses the exit button.
     */
    void on_actionExit_triggered();

    /**
     * Called when the user doubleclicks on a entity in the world outliner.
     * @param item - Item clicked.
     * @param column - Which column that is clicked (not used).
     */
    void on_Outliner_itemDoubleClicked(QTreeWidgetItem *item, int column);

    /**
     * Called when the user presses the cube button.
     */
    void on_spawnCube_triggered();

    /**
     * Called when the user presses the sphere button.
     */
    void on_spawnSphere_triggered();

    /**
     * Called when the user presses the plane button.
     */
    void on_spawnPlane_triggered();

    /**
     * Called when the user presses the BSpline button.
     */
    void on_createBSpline_triggered();

    /**
     * Called when a new item is selected in the world outliner.
     */
    void on_Outliner_itemSelectionChanged();

    /**
     * Called when the user presses the play button.
     */
    void on_actionPlay_triggered();

    /**
     * Called when the user presses the play in editor button.
     */
    void on_actionPlay_in_Editor_triggered();

    /**
     * Called when the user presses the empty entity button.
     */
    void on_actionEmpty_Entity_triggered();

    /**
     * Called when the user presses the open scene button.
     */
    void on_sceneOpen_triggered();

    /**
     * Called when the user presses the create new scene button.
     */
    void on_sceneCreateNew_triggered();

    /**
     * Called when the user presses the save scene button.
     */
    void on_sceneSave_triggered();

    /**
     * Called when the user is righclicking the world outliner.
     */
    void onOutlinerRightClick(const QPoint);

    /**
     * Called when the user presses delete entity in the editor.
     */
    void deleteEntity();
private:

    Ui::MainWindow *ui;

    /**
     * Setsup the child/parent relationship when the user drag and drops a entity on another.
     * @param parent
     */
    void setupChildren(QTreeWidgetItem *parent);

    /**
     * Called when the user presses the play/stop button. Changes the current text on the button depending on what mode you're in.
     */
    void updatePlayButtons();

    /**
     * Used to show the editor panels again after you have stopped the game.
     */
    void showPanels();

    /**
     * Called when the user press play.
     * Telling other classes that the game is starting.
     */
    void playGame();

    /**
     * Called when the user press stop.
     * Telling other classes that the game is stopping.
     */
    void stopGame();

    /// Parent to all the component widgets.
    QWidget* componentsWidgets_ = nullptr;

    /// A pointer to the renderwindow container.
    QWidget *renderWindowContainer_ = nullptr;
};

#endif // MAINWINDOW_H

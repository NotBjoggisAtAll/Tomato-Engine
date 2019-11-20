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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayEntitiesInOutliner();

    void updateRightPanel(Entity entity);

    void addEntityToUi(Entity entity);

    void updateStatusbar(float timePerFrame, float frameCounter, int verticeCounter);

    std::shared_ptr<RenderWindow> renderWindow_ = nullptr;

    void playGame();
    void stopGame();
signals:
    void playGame_signal();
    void stopGame_signal();
    Entity spawnObject(std::string name, std::string path);
    Entity createEntity();
    void loadScene();
    void newScene();
    void saveScene();

private slots:
    void on_actionToggle_Wireframe_triggered();

    void on_actionExit_triggered();

    void on_Outliner_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_spawnCube_triggered();

    void on_spawnSphere_triggered();

    void on_spawnPlane_triggered();

    void on_Outliner_itemSelectionChanged();

    void on_actionPlay_triggered();

    void on_actionPlay_in_Editor_triggered();

    void on_actionEmpty_Entity_triggered();

    void on_sceneOpen_triggered();

    void on_sceneCreateNew_triggered();

    void on_createBSpline_triggered();
    void on_sceneSave_triggered();

private:

    Ui::MainWindow *ui;
    QWidget *renderWindowContainer_ = nullptr;


    //Parent to all componentwidgets
    QWidget* componentsWidgets_{nullptr};

    void setupChildren(QTreeWidgetItem *parent);
    void updatePlayButtons();
    void showPanels();
};

#endif // MAINWINDOW_H

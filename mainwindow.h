#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "types.h"

class QWidget;
class RenderWindow;
class QTreeWidgetItem;
class World;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void DisplayEntitesInOutliner();

    void updateComponentWidgets(Entity entity);

signals:

    void spawnCube();
    void spawnSphere();
    void spawnPlane();


private slots:
    void on_actionToggle_Wireframe_triggered();
    void on_actionExit_triggered();

    void on_Outliner_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_spawnCube_triggered();

    void on_spawnSphere_triggered();

    void on_spawnPlane_triggered();

private:
    void init();

    Ui::MainWindow *ui;
    QWidget *mRenderWindowContainer;
    RenderWindow *mRenderWindow;

    World* world{};

    //Parent to all componentwidgets
    QWidget* widget{nullptr};

};

#endif // MAINWINDOW_H

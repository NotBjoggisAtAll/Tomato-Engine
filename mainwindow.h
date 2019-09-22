#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void DisplayEntitiesInOutliner();

    void updateComponentWidgets(unsigned int EntityID);

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

    void on_Outliner_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QWidget *mRenderWindowContainer;
    RenderWindow *mRenderWindow;

    //Parent to all componentwidgets
    QWidget* widget{nullptr};

    void updateParentChild(QTreeWidgetItem *item);
};

#endif // MAINWINDOW_H

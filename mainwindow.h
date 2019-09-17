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

    void DisplayEntitesInOutliner();

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

private:
    void init();

    Ui::MainWindow *ui;
    QWidget *mRenderWindowContainer;
    RenderWindow *mRenderWindow;

    //Parent to all componentwidgets
    QWidget* widget{nullptr};

};

#endif // MAINWINDOW_H

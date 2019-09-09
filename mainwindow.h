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
private slots:
    void on_actionToggle_Wireframe_triggered();
    void on_actionExit_triggered();

    void on_createObjectButton_clicked();

    void on_Outliner_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    void init();

    Ui::MainWindow *ui;
    QWidget *mRenderWindowContainer;
    RenderWindow *mRenderWindow;
};

#endif // MAINWINDOW_H

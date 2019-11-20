#ifndef ADDCOMPONENTWIDGET_H
#define ADDCOMPONENTWIDGET_H

#include <QWidget>
#include "types.h"

class QMenu;
class MainWindow;

namespace Ui {
class AddComponentWidget;
}

class AddComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddComponentWidget(Entity entity, MainWindow* mainWindow, QWidget *parent = nullptr);
    ~AddComponentWidget();

private slots:
    void on_addButton_clicked();

    void addTransform();
    void addBSpline();
    void addCamera();
    void addCollision();
    void addInput();
    void addLight();
    void addMaterial();
    void addMesh();
    void addNpc();
    void addProjectile();
    void addSound();
private:

    Entity entity_ = -1;
    MainWindow* mainWindow_ = nullptr;
    Ui::AddComponentWidget *ui;

    QMenu* menu_ = nullptr;
};

#endif // ADDCOMPONENTWIDGET_H

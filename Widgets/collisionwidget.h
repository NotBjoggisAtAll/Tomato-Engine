#ifndef COLLISIONWIDGET_H
#define COLLISIONWIDGET_H

#include <QWidget>
#include "types.h"

struct Collision;

namespace Ui {
class CollisionWidget;
}

class CollisionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CollisionWidget(Entity entity, QWidget *parent = nullptr);
    ~CollisionWidget();

private slots:
    void on_pushButton_clicked();

    void remove();
    void updateWidget();
    void on_xMin_valueChanged(double arg1);

    void on_yMin_valueChanged(double arg1);

    void on_zMin_valueChanged(double arg1);

    void on_xMax_valueChanged(double arg1);

    void on_yMax_valueChanged(double arg1);

    void on_zMax_valueChanged(double arg1);

private:
    Entity entity_ = -1;
    Collision* component_ = nullptr;

    Ui::CollisionWidget *ui;
};

#endif // COLLISIONWIDGET_H

#ifndef BSPLINEWIDGET_H
#define BSPLINEWIDGET_H

#include <QWidget>
#include "types.h"
#include "GSL/vector3d.h"

class BSpline;
class Vector3DPicker;

namespace Ui {
class BSplineWidget;
}

class BSplineWidget : public QWidget
{
    Q_OBJECT

public slots:
    void vector3DRecieved(gsl::Vector3D vector);

public:
    explicit BSplineWidget(Entity entityIn, QWidget *parent = nullptr);
    ~BSplineWidget();

private slots:
    void on_addPoint_clicked();

    void on_removePoint_clicked();

    void remove();
    void resetToDefault();

    void on_pushButton_clicked();

private:

    Entity entity_ = -1;
    BSpline* component_ = nullptr;
    Vector3DPicker* vector3DPicker_ = nullptr;
    Ui::BSplineWidget *ui;
};

#endif // BSPLINEWIDGET_H

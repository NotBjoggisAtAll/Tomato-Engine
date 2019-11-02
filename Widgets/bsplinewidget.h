#ifndef BSPLINEWIDGET_H
#define BSPLINEWIDGET_H

#include <QWidget>
#include "types.h"

class BSpline;

namespace Ui {
class BSplineWidget;
}

class BSplineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BSplineWidget(Entity entityIn, QWidget *parent = nullptr);
    ~BSplineWidget();

private:
    Ui::BSplineWidget *ui;

    BSpline* component_ = nullptr;
};

#endif // BSPLINEWIDGET_H

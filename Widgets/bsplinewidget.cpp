#include "bsplinewidget.h"
#include "ui_bsplinewidget.h"
#include "Components/bspline.h"
#include "world.h"

BSplineWidget::BSplineWidget(Entity entityIn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BSplineWidget)
{
    ui->setupUi(this);

    component_ = getWorld()->getComponent<BSpline>(entityIn).value();

    ui->startPos->setText(component_->curve_.getControlPoints().at(0).toQString());
}

BSplineWidget::~BSplineWidget()
{
    delete ui;
}

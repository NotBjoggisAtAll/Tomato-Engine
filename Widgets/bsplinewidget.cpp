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

    ui->startPos->setText(component_->curve_.getControlPoints().front().toQString());
    ui->endPos->setText(component_->curve_.getControlPoints().back().toQString());

    for(auto it = component_->curve_.getControlPoints().begin() + 1; it != component_->curve_.getControlPoints().end() - 1; ++it)
    {
        ui->pointList->addItem(it->toQString());
    }
}

BSplineWidget::~BSplineWidget()
{
    delete ui;
}

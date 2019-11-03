#include "bsplinewidget.h"
#include "ui_bsplinewidget.h"
#include "Components/bspline.h"
#include "world.h"
#include <QString>
#include "Windows/vector3dpicker.h"

BSplineWidget::BSplineWidget(Entity entityIn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BSplineWidget)
{
    ui->setupUi(this);

    component_ = getWorld()->getComponent<BSpline>(entityIn).value();
    if(component_->curve_.getControlPoints().size() == 0)
        return;
    for(auto it = component_->curve_.getControlPoints().begin(); it != component_->curve_.getControlPoints().end(); ++it)
    {
        ui->pointList->addItem(it->toQString());
    }
}

BSplineWidget::~BSplineWidget()
{
    delete ui;
}

void BSplineWidget::vector3DRecieved(gsl::Vector3D vector)
{
    component_->curve_.addControlPoint(vector);
    ui->pointList->addItem(vector.toQString());
    delete vector3DPicker_;
}

void BSplineWidget::on_addPoint_clicked()
{
    vector3DPicker_ = new Vector3DPicker("Add point");
    connect(vector3DPicker_, &Vector3DPicker::sendVector3D, this, &BSplineWidget::vector3DRecieved);
    vector3DPicker_->show();
}

void BSplineWidget::on_removePoint_clicked()
{
    auto item = ui->pointList->takeItem(ui->pointList->currentRow());
    QString string = item->text();
    gsl::Vector3D point;
    auto list = string.split(",");
    auto xS = list.at(0);
    xS.remove(0,1);
    auto zS = list.at(2);
    zS.remove(zS.size()-1,1);

    point.x = static_cast<float>(xS.toDouble());
    point.y = static_cast<float>(list.at(1).toDouble());
    point.z = static_cast<float>(zS.toDouble());
    component_->curve_.removeControlPoint(point);
}

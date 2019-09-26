#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "World.h"
#include "Components/transformcomponent.h"
TransformWidget::TransformWidget(Entity entity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);

    ui->xPosition->setRange(-1000,1000);
    ui->xPosition->setSingleStep(0.1);

    ui->yPosition->setRange(-1000,1000);
    ui->yPosition->setSingleStep(0.1);

    ui->zPosition->setRange(-1000,1000);
    ui->zPosition->setSingleStep(0.1);

    Component = getWorld()->getComponent<Transform>(entity).value_or(nullptr);

    auto Pos = Component->mMatrix.getPosition();

    ui->xPosition->setValue(static_cast<double>(Pos.getX()));
    ui->yPosition->setValue(static_cast<double>(Pos.y));
    ui->zPosition->setValue(static_cast<double>(Pos.z));
}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::on_xPosition_valueChanged(double arg1)
{
    auto p = Component->mMatrix.getPosition();
    Component->mMatrix.setPosition(arg1,p.y,p.z);
}

void TransformWidget::on_yPosition_valueChanged(double arg1)
{
    auto p = Component->mMatrix.getPosition();
    Component->mMatrix.setPosition(p.x,arg1,p.z);
}

void TransformWidget::on_zPosition_valueChanged(double arg1)
{
    auto p = Component->mMatrix.getPosition();
    Component->mMatrix.setPosition(p.x,p.y,arg1);
}

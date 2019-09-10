#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "resourcemanager.h"
TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);

    ui->xPosition->setRange(-1000,1000);
    ui->xPosition->setSingleStep(0.5);

    ui->yPosition->setRange(-1000,1000);
    ui->yPosition->setSingleStep(0.5);

    ui->zPosition->setRange(-1000,1000);
    ui->zPosition->setSingleStep(0.5);

}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::setup(unsigned int EntityID)
{
    Transform = &ResourceManager::instance()->mTransformComponents.at(EntityID);

    auto Pos = Transform->mMatrix.getPosition();

    ui->xPosition->setValue(static_cast<double>(Pos.getX()));
    ui->yPosition->setValue(static_cast<double>(Pos.y));
    ui->zPosition->setValue(static_cast<double>(Pos.z));
}

void TransformWidget::on_xPosition_valueChanged(double arg1)
{
    auto p = Transform->mMatrix.getPosition();
    Transform->mMatrix.setPosition(arg1,p.y,p.z);
}

void TransformWidget::on_yPosition_valueChanged(double arg1)
{
    auto p = Transform->mMatrix.getPosition();
    Transform->mMatrix.setPosition(p.x,arg1,p.z);
}

void TransformWidget::on_zPosition_valueChanged(double arg1)
{
    auto p = Transform->mMatrix.getPosition();
    Transform->mMatrix.setPosition(p.x,p.y,arg1);
}

#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "resourcemanager.h"
TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);

    ui->xDoubleSpinBox->setRange(-1000,1000);
    ui->xDoubleSpinBox->setSingleStep(0.5);

    ui->yDoubleSpinBox->setRange(-1000,1000);
    ui->yDoubleSpinBox->setSingleStep(0.5);

    ui->zDoubleSpinBox->setRange(-1000,1000);
    ui->zDoubleSpinBox->setSingleStep(0.5);

}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::setup(unsigned int EntityID)
{
    Transform = &ResourceManager::instance()->mTransformComponents.at(EntityID);

    auto Pos = Transform->mMatrix.getPosition();

    ui->xDoubleSpinBox->setValue(static_cast<double>(Pos.getX()));
    ui->yDoubleSpinBox->setValue(static_cast<double>(Pos.y));
    ui->zDoubleSpinBox->setValue(static_cast<double>(Pos.z));
}

void TransformWidget::on_xDoubleSpinBox_valueChanged(double arg1)
{
    auto p = Transform->mMatrix.getPosition();
    Transform->mMatrix.setPosition(arg1,p.y,p.z);
}

void TransformWidget::on_yDoubleSpinBox_valueChanged(double arg1)
{
    auto p = Transform->mMatrix.getPosition();
    Transform->mMatrix.setPosition(p.x,arg1,p.z);
}

void TransformWidget::on_zDoubleSpinBox_valueChanged(double arg1)
{
    auto p = Transform->mMatrix.getPosition();
    Transform->mMatrix.setPosition(p.x,p.y,arg1);
}

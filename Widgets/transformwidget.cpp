#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "resourcemanager.h"
TransformWidget::TransformWidget(unsigned int& EntityID, QWidget *parent) :
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

    Component = ResourceManager::instance()->getTransformComponent(EntityID);

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

    if(Component->Child != -1){
        auto child = ResourceManager::instance()->getTransformComponent(static_cast<Entity>(Component->Child));
        child->mMatrix.translate(p.x-arg1,0,0);
    }
}

void TransformWidget::on_yPosition_valueChanged(double arg1)
{
    auto p = Component->mMatrix.getPosition();
    Component->mMatrix.setPosition(p.x,arg1,p.z);


    if(Component->Child != -1){
        auto child = ResourceManager::instance()->getTransformComponent(static_cast<Entity>(Component->Child));
        child->mMatrix.translate(0,arg1-p.y,0);
    }
}

void TransformWidget::on_zPosition_valueChanged(double arg1)
{
    auto p = Component->mMatrix.getPosition();
    Component->mMatrix.setPosition(p.x,p.y,arg1);

    if(Component->Child != -1){
        auto child = ResourceManager::instance()->getTransformComponent(static_cast<Entity>(Component->Child));
        child->mMatrix.translate(0,0,p.z-arg1);

    }
}

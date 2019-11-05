#include "transformwidget.h"
#include "ui_transformwidget.h"
#include "world.h"
#include "Components/transform.h"
#include "Systems/movementsystem.h"

TransformWidget::TransformWidget(Entity entityIn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget),
    entity(entityIn)
{
    ui->setupUi(this);

    ui->xPosition->setRange(-1000,1000);
    ui->xPosition->setSingleStep(0.1);

    ui->yPosition->setRange(-1000,1000);
    ui->yPosition->setSingleStep(0.1);

    ui->zPosition->setRange(-1000,1000);
    ui->zPosition->setSingleStep(0.1);

    ui->xRotation->setRange(-1000,1000);
    ui->xRotation->setSingleStep(0.5);

    ui->yRotation->setRange(-1000,1000);
    ui->yRotation->setSingleStep(0.5);

    ui->zRotation->setRange(-1000,1000);
    ui->zRotation->setSingleStep(0.5);

    ui->xScale->setRange(-1000,1000);
    ui->xScale->setSingleStep(0.1);

    ui->yScale->setRange(-1000,1000);
    ui->yScale->setSingleStep(0.1);

    ui->zScale->setRange(-1000,1000);
    ui->zScale->setSingleStep(0.1);


    Component = getWorld()->getComponent<Transform>(entity).value_or(nullptr);

    auto& Pos = Component->position_;

    ui->xPosition->setValue(static_cast<double>(Pos.x));
    ui->yPosition->setValue(static_cast<double>(Pos.y));
    ui->zPosition->setValue(static_cast<double>(Pos.z));

    auto& Rot = Component->rotation_;

    ui->xRotation->setValue(static_cast<double>(Rot.x));
    ui->yRotation->setValue(static_cast<double>(Rot.y));
    ui->zRotation->setValue(static_cast<double>(Rot.z));

    auto& Scale = Component->scale_;

    ui->xScale->setValue(static_cast<double>(Scale.x));
    ui->yScale->setValue(static_cast<double>(Scale.y));
    ui->zScale->setValue(static_cast<double>(Scale.z));

    initDone = true;
}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::on_xPosition_valueChanged(double arg1)
{
    if(initDone)
    {
        auto& p = Component->position_;
        getWorld()->getSystem<MovementSystem>()->addPosition(entity, {static_cast<float>(arg1 - p.x),0,0});
    }
}

void TransformWidget::on_yPosition_valueChanged(double arg1)
{
    if(initDone)
    {
        auto& p = Component->position_;
        getWorld()->getSystem<MovementSystem>()->addPosition(entity, {0,static_cast<float>(arg1 - p.y),0});
    }
}

void TransformWidget::on_zPosition_valueChanged(double arg1)
{
    if(initDone)
    {
        auto& p = Component->position_;
        getWorld()->getSystem<MovementSystem>()->addPosition(entity, {0,0,static_cast<float>(arg1 - p.z)});
    }
}

void TransformWidget::on_xRotation_valueChanged(double arg1)
{
    auto& r = Component->rotation_;
    Component->rotation_ = {static_cast<float>(arg1), r.y, r.z};
}

void TransformWidget::on_yRotation_valueChanged(double arg1)
{
    auto& r = Component->rotation_;
    Component->rotation_ = {r.x, static_cast<float>(arg1), r.z};
}

void TransformWidget::on_zRotation_valueChanged(double arg1)
{
    auto& r = Component->rotation_;
    Component->rotation_ = {r.x, r.y, static_cast<float>(arg1)};
}

void TransformWidget::on_xScale_valueChanged(double arg1)
{
    auto& s = Component->scale_;
    getWorld()->getSystem<MovementSystem>()->setScale(entity, gsl::Vector3D(static_cast<float>(arg1), s.y, s.z));
}

void TransformWidget::on_yScale_valueChanged(double arg1)
{
    auto& s = Component->scale_;
    getWorld()->getSystem<MovementSystem>()->setScale(entity, gsl::Vector3D(s.x, static_cast<float>(arg1), s.z));
}

void TransformWidget::on_zScale_valueChanged(double arg1)
{
    auto& s = Component->scale_;
    getWorld()->getSystem<MovementSystem>()->setScale(entity, gsl::Vector3D(s.x, s.y, static_cast<float>(arg1)));
}

#include "collisionwidget.h"
#include "ui_collisionwidget.h"
#include "Components/collision.h"
#include "Components/mesh.h"
#include "Factories/resourcefactory.h"
#include "world.h"
#include <QMenu>

CollisionWidget::CollisionWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::CollisionWidget)
{
    ui->setupUi(this);

    component_ = getWorld()->getComponent<Collision>(entity).value();

    ui->xMin->setRange(-1000,1000);
    ui->xMin->setSingleStep(0.1);

    ui->yMin->setRange(-1000,1000);
    ui->yMin->setSingleStep(0.1);

    ui->zMin->setRange(-1000,1000);
    ui->zMin->setSingleStep(0.1);

    ui->xMax->setRange(-1000,1000);
    ui->xMax->setSingleStep(0.5);

    ui->yMax->setRange(-1000,1000);
    ui->yMax->setSingleStep(0.5);

    ui->zMax->setRange(-1000,1000);
    ui->zMax->setSingleStep(0.5);

    ui->xMin->setValue(static_cast<double>(component_->minVector_.x));
    ui->yMin->setValue(static_cast<double>(component_->minVector_.y));
    ui->zMin->setValue(static_cast<double>(component_->minVector_.z));

    ui->xMax->setValue(static_cast<double>(component_->maxVector_.x));
    ui->yMax->setValue(static_cast<double>(component_->maxVector_.y));
    ui->zMax->setValue(static_cast<double>(component_->maxVector_.z));

    if(component_->filepath_ != "")
    {
        ui->label->show();
        ui->meshNameLabel->setText(QString::fromStdString(component_->filepath_));
        ui->meshNameLabel->show();
    }
    else
    {
        ui->label->hide();
        ui->meshNameLabel->hide();
    }
}

CollisionWidget::~CollisionWidget()
{
    delete ui;
}

void CollisionWidget::on_pushButton_clicked()
{
    QMenu menu;
    Mesh* mesh = getWorld()->getComponent<Mesh>(entity_).value_or(nullptr);
    if(mesh)
    {
        if(mesh->filepath_ != "")
            menu.addAction("Update from Mesh", this, &CollisionWidget::updateWidget);
    }
    menu.addAction("Remove", this, &CollisionWidget::remove);
    menu.exec(QCursor::pos());
}

void CollisionWidget::updateWidget()
{
    Mesh* mesh = getWorld()->getComponent<Mesh>(entity_).value_or(nullptr);
    if(!mesh) return;

    getWorld()->removeComponent<Collision>(entity_);
    getWorld()->addComponent(entity_, ResourceFactory::get()->getCollision(mesh->filepath_));
    component_ = getWorld()->getComponent<Collision>(entity_).value();
    ui->xMin->setValue(static_cast<double>(component_->minVector_.x));
    ui->yMin->setValue(static_cast<double>(component_->minVector_.y));
    ui->zMin->setValue(static_cast<double>(component_->minVector_.z));

    ui->xMax->setValue(static_cast<double>(component_->maxVector_.x));
    ui->yMax->setValue(static_cast<double>(component_->maxVector_.y));
    ui->zMax->setValue(static_cast<double>(component_->maxVector_.z));

    if(component_->filepath_ != "")
    {
        ui->label->show();
        ui->meshNameLabel->setText(QString::fromStdString(component_->filepath_));
        ui->meshNameLabel->show();
    }
    else
    {
        ui->label->hide();
        ui->meshNameLabel->hide();
    }
}

void CollisionWidget::remove()
{
    getWorld()->removeComponent<Collision>(entity_);
    hide();
}

void CollisionWidget::on_xMin_valueChanged(double arg1)
{
    component_->minVector_.x = static_cast<float>(arg1);
}

void CollisionWidget::on_yMin_valueChanged(double arg1)
{
    component_->minVector_.y = static_cast<float>(arg1);
}

void CollisionWidget::on_zMin_valueChanged(double arg1)
{
    component_->minVector_.z = static_cast<float>(arg1);
}

void CollisionWidget::on_xMax_valueChanged(double arg1)
{
    component_->maxVector_.x = static_cast<float>(arg1);
}

void CollisionWidget::on_yMax_valueChanged(double arg1)
{
    component_->maxVector_.y = static_cast<float>(arg1);
}

void CollisionWidget::on_zMax_valueChanged(double arg1)
{
    component_->maxVector_.z = static_cast<float>(arg1);
}

#include "projectilewidget.h"
#include "ui_projectilewidget.h"
#include "Components/projectile.h"
#include "world.h"
#include <QMenu>

ProjectileWidget::ProjectileWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::ProjectileWidget)
{
    ui->setupUi(this);

    component_ = getWorld()->getComponent<Projectile>(entity).value();

    ui->speedSpinBox->setRange(0,100);
    ui->lifeTimeSpinBox->setRange(0,100);

    ui->speedSpinBox->setSingleStep(0.1);
    ui->lifeTimeSpinBox->setSingleStep(0.1);

    ui->speedSpinBox->setValue(static_cast<double>(component_->speed_));
    ui->lifeTimeSpinBox->setValue(static_cast<double>(component_->lifetime_));
}

ProjectileWidget::~ProjectileWidget()
{
    delete ui;
}

void ProjectileWidget::on_speedSpinBox_valueChanged(double arg1)
{
    component_->speed_ = static_cast<float>(arg1);
}

void ProjectileWidget::on_lifeTimeSpinBox_valueChanged(double arg1)
{
    component_->lifetime_ = static_cast<float>(arg1);
}

void ProjectileWidget::on_moreButton_clicked()
{
    QMenu subMenu;

    subMenu.addAction("Reset to default", this, &ProjectileWidget::resetToDefault);
    subMenu.addAction("Remove", this, &ProjectileWidget::remove);

    subMenu.exec(QCursor::pos());
}

void ProjectileWidget::resetToDefault()
{
    getWorld()->removeComponent<Projectile>(entity_);
    getWorld()->addComponent(entity_, Projectile());
    component_ = getWorld()->getComponent<Projectile>(entity_).value();
    ui->speedSpinBox->setValue(static_cast<double>(component_->speed_));
    ui->lifeTimeSpinBox->setValue(static_cast<double>(component_->lifetime_));
}

void ProjectileWidget::remove()
{
    getWorld()->removeComponent<Projectile>(entity_);
    hide();
}

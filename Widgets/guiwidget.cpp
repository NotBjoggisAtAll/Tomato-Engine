#include "guiwidget.h"
#include "ui_guiwidget.h"
#include "Components/gui.h"
#include "world.h"
#include <QMenu>

GUIWidget::GUIWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::GUIWidget)
{
    ui->setupUi(this);

    component_ = getWorld()->getComponent<GUI>(entity_).value();

    ui->xPos->setRange(-1,1);
    ui->yPos->setRange(-1,1);
    ui->xScale->setRange(0,1);
    ui->yScale->setRange(0,1);

    ui->xPos->setSingleStep(0.05);
    ui->yPos->setSingleStep(0.05);
    ui->xScale->setSingleStep(0.05);
    ui->yScale->setSingleStep(0.05);

    ui->xPos->setValue(static_cast<double>(component_->position_.x));
    ui->yPos->setValue(static_cast<double>(component_->position_.y));
    ui->xScale->setValue(static_cast<double>(component_->scale_.x));
    ui->yScale->setValue(static_cast<double>(component_->scale_.y));
}

GUIWidget::~GUIWidget()
{
    delete ui;
}

void GUIWidget::on_pushButton_clicked()
{
    QMenu menu;
    menu.addAction("Reset to default", this, &GUIWidget::reset);
    menu.addAction("Remove", this, &GUIWidget::remove);
    menu.exec(QCursor::pos());
}

void GUIWidget::remove()
{
    getWorld()->removeComponent<GUI>(entity_);
    hide();
}

void GUIWidget::reset()
{
    component_->position_ = gsl::Vector2D(0);
    component_->scale_ = gsl::Vector2D(1);

    ui->xPos->setValue(static_cast<double>(component_->position_.x));
    ui->yPos->setValue(static_cast<double>(component_->position_.y));
    ui->xScale->setValue(static_cast<double>(component_->scale_.x));
    ui->yScale->setValue(static_cast<double>(component_->scale_.y));
}

void GUIWidget::on_xPos_valueChanged(double arg1)
{
    component_->position_.x = static_cast<float>(arg1);
}

void GUIWidget::on_yPos_valueChanged(double arg1)
{
    component_->position_.y = static_cast<float>(arg1);
}

void GUIWidget::on_xScale_valueChanged(double arg1)
{
    component_->scale_.x = static_cast<float>(arg1);
}

void GUIWidget::on_yScale_valueChanged(double arg1)
{
    component_->scale_.y = static_cast<float>(arg1);
}

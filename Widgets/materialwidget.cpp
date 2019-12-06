#include "materialwidget.h"
#include "ui_materialwidget.h"
#include "Factories/texturefactory.h"
#include "Managers/shadermanager.h"
#include "Factories/texturefactory.h"
#include "Components/material.h"
#include "world.h"
#include <QMenu>
#include <QFile>

MaterialWidget::MaterialWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::MaterialWidget)
{
    ui->setupUi(this);

    component_ = getWorld()->getComponent<Material>(entity_).value();

    ui->rColor->setRange(0,1);
    ui->gColor->setRange(0,1);
    ui->bColor->setRange(0,1);
    ui->rColor->setSingleStep(0.05);
    ui->gColor->setSingleStep(0.05);
    ui->bColor->setSingleStep(0.05);

    ui->rColor->setValue(static_cast<double>(component_->color_.x));
    ui->gColor->setValue(static_cast<double>(component_->color_.y));
    ui->bColor->setValue(static_cast<double>(component_->color_.z));

    if(component_->textureFile_ == "")
    {
        ui->textureWidget->setVisible(false);
    }
    else
    {
        ui->textureName->setText(QString::fromStdString(component_->textureFile_));
    }

    for(const auto& shader : ShaderManager::get()->getShaders())
    {
        ui->shaderBox->addItem(QString::fromStdString(shader.first));
    }

    ui->shaderBox->setCurrentText(QString::fromStdString(component_->shader_->mShaderName));
}

MaterialWidget::~MaterialWidget()
{
    delete ui;
}

void MaterialWidget::on_pushButton_clicked()
{
    QMenu menu;
    menu.addAction("Remove", this, &MaterialWidget::remove);
    menu.exec(QCursor::pos());
}

void MaterialWidget::remove()
{
    getWorld()->removeComponent<Material>(entity_);
    hide();
}

void MaterialWidget::on_rColor_valueChanged(double arg1)
{
    component_->color_.x = static_cast<float>(arg1);
}

void MaterialWidget::on_gColor_valueChanged(double arg1)
{
    component_->color_.y = static_cast<float>(arg1);
}

void MaterialWidget::on_bColor_valueChanged(double arg1)
{
    component_->color_.z = static_cast<float>(arg1);
}

void MaterialWidget::on_shaderBox_currentIndexChanged(const QString &arg1)
{
    if(!(arg1 == "textureshader" || arg1 == "guishader" || ui->shaderBox->currentIndex() == 0))
    {
        ui->textureWidget->setVisible(false);
    }
    else
    {
        ui->textureWidget->setVisible(true);
    }
    if(!(ui->shaderBox->currentIndex() == 0))
    component_->shader_ = ShaderManager::get()->getShader(arg1.toStdString());
}

void MaterialWidget::on_textureName_editingFinished()
{
    qDebug() << ui->textureName->text();
    if(ui->textureName->text().isEmpty())
    {
        component_->textureFile_ = "";
        component_->textureUnit_ = 0;
        return;
    }
    auto id = TextureFactory::get()->loadTexture(ui->textureName->text().toStdString());
    if(id.has_value())
    {
        ui->textureName->setStyleSheet("");
        component_->textureFile_  = ui->textureName->text().toStdString();
        component_->textureUnit_ = id.value();
    }
    else
    {
        ui->textureName->setStyleSheet("color: red");
    }
}

void MaterialWidget::on_textureName_textEdited(const QString &/*arg1*/)
{
    ui->textureName->setStyleSheet("");
}

#include "meshwidget.h"
#include "ui_meshwidget.h"
#include "resourcemanager.h"
#include "Components/meshcomponent.h"

MeshWidget::MeshWidget(Entity EntityID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshWidget)
{
    ui->setupUi(this);

    Component = ResourceManager::instance()->getMeshComponent(EntityID);

    ui->isVisible->setChecked(Component->isVisible);

}

MeshWidget::~MeshWidget()
{
    delete ui;
}


void MeshWidget::on_isVisible_toggled(bool checked)
{
    Component->isVisible = checked;
}

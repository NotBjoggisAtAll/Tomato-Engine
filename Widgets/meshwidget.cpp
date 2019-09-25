#include "meshwidget.h"
#include "ui_meshwidget.h"
#include "Components/meshcomponent.h"
#include "World.h"

extern World world;

MeshWidget::MeshWidget(Entity entity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshWidget)
{
    ui->setupUi(this);

    Component = World::getWorld()->getComponent<Mesh>(entity).value();

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

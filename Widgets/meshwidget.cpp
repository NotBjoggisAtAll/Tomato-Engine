#include "meshwidget.h"
#include "ui_meshwidget.h"
#include "Components/mesh.h"
#include "world.h"
#include "resourcefactory.h"
#include <QFileDialog>

extern World world;

MeshWidget::MeshWidget(Entity entity_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshWidget), entity(entity_)
{
    ui->setupUi(this);

    Component = getWorld()->getComponent<Mesh>(entity).value();

    ui->isVisible->setChecked(Component->isVisible_);

}

MeshWidget::~MeshWidget()
{
    delete ui;
}


void MeshWidget::on_isVisible_toggled(bool checked)
{
    Component->isVisible_ = checked;
}

void MeshWidget::on_changeMeshButton_clicked()
{
    QFileDialog fileDialog;
    fileDialog.setNameFilter("*.obj");
    QFileInfo fileInfo = fileDialog.getOpenFileName(this,"Open file","../INNgine2019/Assets","*.obj *.txt *.terrain");

    std::string fileName =  fileInfo.fileName().toStdString();

    if(!fileName.empty())
    {
        qDebug() << QString::fromStdString(fileName);
        getWorld()->removeComponent<Mesh>(entity);
        getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh(fileName));
        getWorld()->removeComponent<Collision>(entity);
        getWorld()->addComponent(entity, ResourceFactory::get()->getCollision(fileName));
    }
}

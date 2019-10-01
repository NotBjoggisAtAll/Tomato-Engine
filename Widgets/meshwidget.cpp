#include "meshwidget.h"
#include "ui_meshwidget.h"
#include "Components/meshcomponent.h"
#include "World.h"
#include "resourcefactory.h"
#include <QFileDialog>

extern World world;

MeshWidget::MeshWidget(Entity entity_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshWidget), entity(entity_)
{
    ui->setupUi(this);

    Component = getWorld()->getComponent<Mesh>(entity).value();

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

void MeshWidget::on_changeMeshButton_clicked()
{
    QFileDialog fileDialog;
    fileDialog.setNameFilter("*.obj");
    QString QfileName = fileDialog.getOpenFileName(this,"Open file","../INNgine2019/Assets","*.obj *.txt");
    std::string fileName = QfileName.toStdString();

    if(!fileName.empty())
    {
        qDebug() << QString::fromStdString(fileName);
        getWorld()->removeComponent<Mesh>(entity);
        getWorld()->addComponent(entity, ResourceFactory::instance()->loadMesh(fileName));
    }
}

#include "meshwidget.h"
#include "ui_meshwidget.h"
#include "Components/mesh.h"
#include "world.h"
#include "resourcefactory.h"
#include <QMenu>
#include <QFileDialog>

extern World world;

MeshWidget::MeshWidget(Entity entity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshWidget), entity_(entity)
{
    ui->setupUi(this);

    Component = getWorld()->getComponent<Mesh>(entity).value();

    ui->isVisible->setChecked(Component->isVisible_);
    ui->meshNameLabel->setText(QString::fromStdString(Component->filepath_));

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
        getWorld()->removeComponent<Mesh>(entity_);
        getWorld()->addComponent(entity_, ResourceFactory::get()->loadMesh(fileName));
    }
}

void MeshWidget::remove()
{
    getWorld()->removeComponent<Mesh>(entity_);
    hide();
}

void MeshWidget::on_moreButton_clicked()
{
    QMenu subMenu;

    // Add actions here with name and slot to execute when action is pressed
    subMenu.addAction("Remove", this, &MeshWidget::remove);

    subMenu.exec(QCursor::pos());
}

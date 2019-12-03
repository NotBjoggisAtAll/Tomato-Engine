#include "meshwidget.h"
#include "ui_meshwidget.h"
#include "Factories/resourcefactory.h"
#include "constants.h"
#include "Components/mesh.h"
#include "world.h"
#include <QMenu>
#include <QFileDialog>

extern World world;

MeshWidget::MeshWidget(Entity entity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshWidget), entity_(entity)
{
    ui->setupUi(this);

    component_ = getWorld()->getComponent<Mesh>(entity).value();

    ui->isVisible->setChecked(component_->isVisible_);
    ui->meshNameLabel->setText(QString::fromStdString(component_->filepath_));

}

MeshWidget::~MeshWidget()
{
    delete ui;
}

void MeshWidget::on_isVisible_toggled(bool checked)
{
    component_->isVisible_ = checked;
}

void MeshWidget::on_changeMeshButton_clicked()
{
    QFileDialog fileDialog;
    fileDialog.setNameFilter("*.obj");
    QFileInfo fileInfo = fileDialog.getOpenFileName(this,"Open file",QString::fromStdString(gsl::assetFilePath),"*.obj *.txt *.terrain");

    std::string fileName =  fileInfo.fileName().toStdString();

    if(!fileName.empty())
    {
        getWorld()->removeComponent<Mesh>(entity_);
        getWorld()->addComponent(entity_, ResourceFactory::get()->loadMesh(fileName));
        component_ = getWorld()->getComponent<Mesh>(entity_).value();
    }
    ui->meshNameLabel->setText(QString::fromStdString(component_->filepath_));
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

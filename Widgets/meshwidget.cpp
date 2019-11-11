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
    setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, &QWidget::customContextMenuRequested, this, &MeshWidget::ProvideContextMenu);

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
        getWorld()->removeComponent<Mesh>(entity_);
        getWorld()->addComponent(entity_, ResourceFactory::get()->loadMesh(fileName));
        getWorld()->removeComponent<Collision>(entity_);
        getWorld()->addComponent(entity_, ResourceFactory::get()->getCollision(fileName));
    }

    unsigned int i = 1;
    int j = i;
    qDebug() << j;
}

void MeshWidget::ProvideContextMenu(const QPoint &point)
{
    QMenu subMenu;

    // Add actions here with name and slot to execute when action is pressed
    subMenu.addAction("Remove", this, &MeshWidget::Remove);

    QPoint globalPos = mapToGlobal(point);

    subMenu.exec(globalPos);
}

void MeshWidget::Remove()
{
    getWorld()->removeComponent<Mesh>(entity_);
    destroy();
}

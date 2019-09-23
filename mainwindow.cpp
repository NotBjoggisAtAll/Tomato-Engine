#include "innpch.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSurfaceFormat>
#include <QDesktopWidget>

#include "Widgets/transformwidget.h"
#include "Widgets/meshwidget.h"
#include "Widgets/soundwidget.h"
#include "renderwindow.h"
#include "resourcemanager.h"
#include "entitymanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //This will contain the setup of the OpenGL surface we will render into
    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setDepthBufferSize(24);
    format.setSamples(8);
    //Turn off VSync. If this is set to 1, VSync is on - default behaviour
    format.setSwapInterval(0);

    //We have a format for the OpenGL window, so let's make it:
    mRenderWindow = new RenderWindow(format, this);

    if (!mRenderWindow->context()) {
        qDebug() << "Failed to create context. Can not continue. Quits application!";
        delete mRenderWindow;
        return;
    }

    mRenderWindowContainer = QWidget::createWindowContainer(mRenderWindow);
    ui->OpenGLLayout->addWidget(mRenderWindowContainer);
    mRenderWindowContainer->setFocus();

    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setWidgetResizable(true);

}

MainWindow::~MainWindow()
{
    delete mRenderWindow;
    delete ui;
}

void MainWindow::initWorldOutliner()
{
    ui->Outliner->init();
}


void MainWindow::updateParentChild(QTreeWidgetItem* item)
{
    for(int i=0; i<item->childCount();i++)
    {
        EntityManager::instance()->addChild(item->text(1).toInt(),item->child(i)->text(1).toInt());
        updateParentChild(item->child(i));
    }
}

void MainWindow::on_actionToggle_Wireframe_triggered()
{
    mRenderWindow->toggleWireframe();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::updateComponentWidgets(unsigned int EntityID)
{
    if(widget)
        delete widget;

    widget = new QWidget();
    ui->scrollArea->setWidget(widget);
    QVBoxLayout* layout = new QVBoxLayout();
    widget->setLayout(layout);

    auto Manager = ResourceManager::instance();

    if(Manager->getTransformComponent(EntityID))
        layout->addWidget(new TransformWidget(EntityID));

    if(Manager->getMeshComponent(EntityID))
        layout->addWidget(new MeshWidget(EntityID));

    if(Manager->getSoundComponent(EntityID))
        layout->addWidget(new SoundWidget(EntityID));
}

void MainWindow::on_Outliner_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    updateComponentWidgets((item->text(1)).toUInt());
}

void MainWindow::on_spawnCube_triggered()
{
    emit spawnCube();
}

void MainWindow::on_spawnSphere_triggered()
{
    emit spawnSphere();
}

void MainWindow::on_spawnPlane_triggered()
{
    emit spawnPlane();
}

void MainWindow::on_Outliner_itemClicked(QTreeWidgetItem *item, int column)
{
    for(auto& Entity : EntityManager::instance()->mEntities)
    {
        EntityManager::instance()->removeRelationship(Entity.first);
    }
    for(unsigned int i=0; i<ui->Outliner->topLevelItemCount(); i++)
    {
        updateParentChild(ui->Outliner->topLevelItem(i));
    }
}

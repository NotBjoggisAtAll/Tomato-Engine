#include "innpch.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSurfaceFormat>
#include <QDesktopWidget>

#include "Widgets/transformwidget.h"
#include "Widgets/meshwidget.h"
#include "Widgets/soundwidget.h"
#include "renderwindow.h"

#include "Components/allcomponents.h"
#include "World.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete mRenderWindow;
    delete ui;
}

void MainWindow::DisplayEntitesInOutliner()
{
    ui->Outliner->clear();
    for(auto Entity : world->getEntities())
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();

        item->setText(0, QString::fromStdString(Entity.second));
        item->setText(1, QString::number(Entity.first));
        ui->Outliner->addTopLevelItem(item);
    }
}

void MainWindow::init()
{
    //This will contain the setup of the OpenGL surface we will render into
    QSurfaceFormat format;

    //OpenGL v 4.1 - (Ole Flatens Mac does not support higher than this...)
    //you can try other versions, but then have to update RenderWindow and Shader
    //to inherit from other than QOpenGLFunctions_4_1_Core
    format.setVersion(4, 1);
    //Using the main profile for OpenGL - no legacy code permitted
    format.setProfile(QSurfaceFormat::CoreProfile);
    //A QSurface can be other types that OpenGL
    format.setRenderableType(QSurfaceFormat::OpenGL);

    //This should activate OpenGL debug Context used in RenderWindow::startOpenGLDebugger().
    //This line (and the startOpenGLDebugger() and checkForGLerrors() in RenderWindow class)
    //can be deleted, but it is nice to have OpenGL debug info!
    format.setOption(QSurfaceFormat::DebugContext);

    // The renderer will need a depth buffer - (not requiered to set in glfw-tutorials)
    format.setDepthBufferSize(24);

    //Set the number of samples used for multisampling
    format.setSamples(8);

    //Turn off VSync. If this is set to 1, VSync is on - default behaviour
    format.setSwapInterval(0);

    //Just prints out what OpenGL format we will get
    // - this can be deleted
    qDebug() << "Requesting surface format: " << format;

    //We have a format for the OpenGL window, so let's make it:
    mRenderWindow = new RenderWindow(format, this);
    //Check if renderwindow did initialize, else prints error and quit
    if (!mRenderWindow->context()) {
        qDebug() << "Failed to create context. Can not continue. Quits application!";
        delete mRenderWindow;
        return;
    }

    //The OpenGL RenderWindow got made, so continuing the setup:
    //We put the RenderWindow inside a QWidget so we can put in into a
    //layout that is made in the .ui-file
    mRenderWindowContainer = QWidget::createWindowContainer(mRenderWindow);
    //OpenGLLayout is made in the .ui-file!
    ui->OpenGLLayout->addWidget(mRenderWindowContainer);

    //sets the keyboard input focus to the RenderWindow when program starts
    // - can be deleted, but then you have to click inside the renderwindow to get the focus
    mRenderWindowContainer->setFocus();

    //Set size of program in % of available screen
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);


    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setWidgetResizable(true);

    world = World::getWorld();

}

void MainWindow::on_actionToggle_Wireframe_triggered()
{
    mRenderWindow->toggleWireframe();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::updateComponentWidgets(Entity entity)
{
    if(widget)
        delete widget;

    widget = new QWidget();
    ui->scrollArea->setWidget(widget);
    QVBoxLayout* layout = new QVBoxLayout();
    widget->setLayout(layout);

    Transform* transform = world->getComponent<Transform>(entity).value_or(nullptr);
    if(transform)
        layout->addWidget(new TransformWidget(entity));

    Mesh* mesh = world->getComponent<Mesh>(entity).value_or(nullptr);
    if(mesh)
        layout->addWidget(new MeshWidget(entity));

    Sound* sound = world->getComponent<Sound>(entity).value_or(nullptr);
    if(sound)
        layout->addWidget(new SoundWidget(entity));
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

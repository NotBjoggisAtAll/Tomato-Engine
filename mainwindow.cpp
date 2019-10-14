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
    QSurfaceFormat format;

    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setDepthBufferSize(24);
    format.setSamples(8);
    format.setSwapInterval(0); //Turn off VSync

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

    setWindowIcon(QIcon("../INNgine2019/Icons/tomatobotBIG.png"));
}

MainWindow::~MainWindow()
{
    delete mRenderWindow;
    delete ui;
}

void MainWindow::DisplayEntitesInOutliner()
{
    ui->Outliner->clear();
    for(auto& Entity : getWorld()->getEntities())
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        auto data = getWorld()->getComponent<EntityData>(Entity).value_or(nullptr);
        item->setText(0, QString::fromStdString(data->name));
        item->setText(1, QString::number(Entity));
        ui->Outliner->addTopLevelItem(item);
    }
}

void MainWindow::addEntityToUi(Entity entity)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    auto data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);
    item->setText(0, QString::fromStdString(data->name));
    item->setText(1, QString::number(entity));
    ui->Outliner->addTopLevelItem(item);
}

void MainWindow::on_actionToggle_Wireframe_triggered()
{
    mRenderWindow->toggleWireframe();
}

void MainWindow::on_actionExit_triggered()
{
    if(getWorld()->bGameRunning)
        stopGame();
    else
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

    Transform* transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if(transform)
        layout->addWidget(new TransformWidget(entity, mRenderWindow->mMovementSystem));

    Mesh* mesh = getWorld()->getComponent<Mesh>(entity).value_or(nullptr);
    if(mesh)
        layout->addWidget(new MeshWidget(entity));

    Sound* sound = getWorld()->getComponent<Sound>(entity).value_or(nullptr);
    if(sound)
        layout->addWidget(new SoundWidget(entity));

}

void MainWindow::on_Outliner_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    updateComponentWidgets((item->text(1)).toInt());
}

void MainWindow::on_spawnCube_triggered()
{
    emit spawnObject("Cube","box2.txt");
}

void MainWindow::on_spawnSphere_triggered()
{
    emit spawnObject("Sphere","sphere");
}

void MainWindow::on_spawnPlane_triggered()
{
    emit spawnObject("Plane","plane");
}

void MainWindow::on_Outliner_itemSelectionChanged()
{
    for(auto& Entity : getWorld()->getEntities())
    {
        auto data = getWorld()->getComponent<EntityData>(Entity).value_or(nullptr);
        if(data)
        {
            data->parent = -1;
            data->children.clear();
        }
    }

    for (int i = 0; i < ui->Outliner->topLevelItemCount(); ++i)
    {
        setupChildren(ui->Outliner->topLevelItem(i));
    }
}

void MainWindow::setupChildren(QTreeWidgetItem* parent)
{

    auto parentData = getWorld()->getComponent<EntityData>(parent->text(1).toInt()).value_or(nullptr);

    for(int j = 0; j < parent->childCount(); ++j)
    {
        auto childData = getWorld()->getComponent<EntityData>((parent->child(j)->text(1).toInt())).value_or(nullptr);
        if(childData)
        {
            parentData->children.push_back((parent->child(j)->text(1).toInt()));
            childData->parent = parent->text(1).toInt();
            setupChildren(parent->child(j));
        }
    }
}

void MainWindow::showPanels()
{
    ui->leftPanel->show();
    ui->rightPanel->show();
}

void MainWindow::on_actionPlay_triggered()
{
    updatePlayButtons();
    if(getWorld()->bGameRunning)
        stopGame();
    else
    {
        getWorld()->bGameRunning = true;
        ui->leftPanel->hide();
        ui->rightPanel->hide();
    }
}

void MainWindow::on_actionPlay_in_Editor_triggered()
{
    updatePlayButtons();
    if(getWorld()->bGameRunning)
        stopGame();
    else
        getWorld()->bGameRunning = true;
}

void MainWindow::updatePlayButtons()
{
    QString buttonText = getWorld()->bGameRunning ? "Play (Fullscreen)" : "Stop";
    ui->actionPlay->setText(buttonText);

    buttonText = getWorld()->bGameRunning ? "Play in Editor" : "Stop";
    ui->actionPlay_in_Editor->setText(buttonText);
}

void MainWindow::stopGame()
{
    updatePlayButtons();
    getWorld()->bGameRunning = false;
    showPanels();
}

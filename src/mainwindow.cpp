#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Widgets/allcomponentwidgets.h"
#include "Components/allcomponents.h"
#include "Windows/vector3dpicker.h"
#include "renderwindow.h"
#include "constants.h"
#include "world.h"
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QAbstractItemView>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setWidgetResizable(true);

    ui->Outliner->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->Outliner, &QWidget::customContextMenuRequested, this, &MainWindow::onOutlinerRightClick);

    setWindowIcon(QIcon("../Tomato-Engine/Icons/tomatobotBIG.png"));

    renderWindow_ = std::make_shared<RenderWindow>();
    renderWindowContainer_ = QWidget::createWindowContainer(renderWindow_.get());
    ui->OpenGLLayout->addWidget(renderWindowContainer_);
    renderWindowContainer_->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOutlinerRightClick(const QPoint point)
{
    ui->Outliner->selectionModel()->clearSelection();
    auto item = ui->Outliner->itemAt(point);
    if(!item) return;
    item->setSelected(true);

    QMenu menu;
    menu.addAction("Delete", this, &MainWindow::deleteEntity);
    menu.exec(QCursor::pos());
}

void MainWindow::deleteEntity()
{
    getWorld()->destroyEntityLater(ui->Outliner->currentItem()->text(1).toInt());
    updateRightPanel(-1);
}

void MainWindow::displayEntitiesInOutliner()
{
    ui->Outliner->clear();
    for(auto& entity : getWorld()->getEntities())
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        auto data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);
        if(data)
        {
            if(data->name_.front() == '_')
                continue;
            item->setText(0, QString::fromStdString(data->name_));
            item->setText(1, QString::number(entity));
            ui->Outliner->addTopLevelItem(item);
        }
    }
}

void MainWindow::addEntityToOutliner(Entity entity)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    auto data = getWorld()->getComponent<EntityData>(entity).value_or(nullptr);
    item->setText(0, QString::fromStdString(data->name_));
    item->setText(1, QString::number(entity));
    ui->Outliner->addTopLevelItem(item);
}

void MainWindow::updateStatusbar(float timePerFrame, float frameCounter, int verticeCounter)
{
    statusBar()->showMessage(" | Time pr FrameDraw: "
                             + QString::number(static_cast<double>(timePerFrame), 'g', 4)
                             + " s  |  " + "FPS: "
                             + QString::number(static_cast<double>(frameCounter), 'g', 4)
                             + " | Vertice count: "
                             + QString::number(verticeCounter));
}

void MainWindow::on_actionToggle_Wireframe_triggered()
{
    renderWindow_->toggleWireframe();
}

void MainWindow::on_actionExit_triggered()
{
    if(getWorld()->bGameRunning)
        stopGame();
    else
        close();
}

void MainWindow::updateRightPanel(Entity entity)
{
    if(componentsWidgets_)
    {
        delete componentsWidgets_;
        componentsWidgets_ = nullptr;
    }

    if(entity == -1)
        return;

    componentsWidgets_ = new QWidget();
    ui->scrollArea->setWidget(componentsWidgets_);
    QVBoxLayout* layout = new QVBoxLayout();
    componentsWidgets_->setLayout(layout);
    layout->setMargin(0);

    Transform* transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
    if(transform)
        layout->addWidget(new TransformWidget(entity));

    Material* material = getWorld()->getComponent<Material>(entity).value_or(nullptr);
    if(material)
        layout->addWidget(new MaterialWidget(entity));

    Mesh* mesh = getWorld()->getComponent<Mesh>(entity).value_or(nullptr);
    if(mesh)
        layout->addWidget(new MeshWidget(entity));

    Collision* collision = getWorld()->getComponent<Collision>(entity).value_or(nullptr);
    if(collision)
        layout->addWidget(new CollisionWidget(entity));

    Sound* sound = getWorld()->getComponent<Sound>(entity).value_or(nullptr);
    if(sound)
        layout->addWidget(new SoundWidget(entity));

    BSpline* spline = getWorld()->getComponent<BSpline>(entity).value_or(nullptr);
    if(spline)
        layout->addWidget(new BSplineWidget(entity));

    Script* script = getWorld()->getComponent<Script>(entity).value_or(nullptr);
    if(script)
        layout->addWidget(new ScriptWidget(entity));

    Projectile* projectile = getWorld()->getComponent<Projectile>(entity).value_or(nullptr);
    if(projectile)
        layout->addWidget(new ProjectileWidget(entity));

    Input* input = getWorld()->getComponent<Input>(entity).value_or(nullptr);
    if(input)
        layout->addWidget(new InputWidget(entity));

    GUI* gui = getWorld()->getComponent<GUI>(entity).value_or(nullptr);
    if(gui)
        layout->addWidget(new GUIWidget(entity));

    AddComponentWidget* addComponentWidget = new AddComponentWidget(entity, componentsWidgets_);
    layout->addWidget(addComponentWidget);

    connect(addComponentWidget, &AddComponentWidget::updateComponentPanel, this, &MainWindow::updateRightPanel);

}

void MainWindow::on_Outliner_itemDoubleClicked(QTreeWidgetItem *item, int)
{
    updateRightPanel((item->text(1)).toInt());
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

void MainWindow::on_actionEmpty_Entity_triggered()
{
    Entity entity = emit createEntity();
    addEntityToOutliner(entity);
}

void MainWindow::on_Outliner_itemSelectionChanged()
{
    for(auto& Entity : getWorld()->getEntities())
    {
        auto data = getWorld()->getComponent<EntityData>(Entity).value_or(nullptr);
        if(data)
        {
            data->parent_ = -1;
            data->children_.clear();
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
            parentData->children_.push_back((parent->child(j)->text(1).toInt()));
            childData->parent_ = parent->text(1).toInt();
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
    {
        stopGame();
    }
    else
    {
        playGame();
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
        playGame();
}

void MainWindow::updatePlayButtons()
{
    QString buttonText = getWorld()->bGameRunning ? "Play (Fullscreen)" : "Stop";
    ui->actionPlay->setText(buttonText);

    buttonText = getWorld()->bGameRunning ? "Play in Editor" : "Stop";
    ui->actionPlay_in_Editor->setText(buttonText);
}

void MainWindow::playGame()
{
    emit playGame_signal();
    getWorld()->bGameRunning = true;
}

void MainWindow::stopGame()
{
    emit stopGame_signal();
    updatePlayButtons();
    getWorld()->bGameRunning = false;
    updateRightPanel(-1);
    showPanels();
}


void MainWindow::on_sceneOpen_triggered()
{
    emit loadScene();
}

void MainWindow::on_sceneCreateNew_triggered()
{
    emit newScene();
}

void MainWindow::on_createBSpline_triggered()
{
    emit spawnObject("BSpline", "BSpline");
}

void MainWindow::on_sceneSave_triggered()
{
    emit saveScene();
}

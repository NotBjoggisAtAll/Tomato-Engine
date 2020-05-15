#include "addcomponentwidget.h"
#include "ui_addcomponentwidget.h"
#include "Components/allcomponents.h"
#include "Managers/shadermanager.h"
#include "world.h"
#include <QDebug>
#include <QMenu>

AddComponentWidget::AddComponentWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::AddComponentWidget)
{
    ui->setupUi(this);
}

AddComponentWidget::~AddComponentWidget()
{
    delete ui;
}

void AddComponentWidget::on_addButton_clicked()
{
    QMenu menu;
    if(!getWorld()->getComponent<Transform>(entity_).value_or(nullptr))
        menu.addAction("Transform", this, &AddComponentWidget::addTransform);
    if(!getWorld()->getComponent<Collision>(entity_).value_or(nullptr))
        menu.addAction("Collision", this, &AddComponentWidget::addCollision);
    if(!getWorld()->getComponent<Mesh>(entity_).value_or(nullptr))
        menu.addAction("Mesh", this, &AddComponentWidget::addMesh);
    if(!getWorld()->getComponent<Material>(entity_).value_or(nullptr))
        menu.addAction("Material", this, &AddComponentWidget::addMaterial);
    if(!getWorld()->getComponent<Sound>(entity_).value_or(nullptr))
        menu.addAction("Sound", this, &AddComponentWidget::addSound);
    if(menu.actions().size() == 0)
        menu.addSeparator();
    if(!getWorld()->getComponent<BSpline>(entity_).value_or(nullptr))
        menu.addAction("BSpline", this, &AddComponentWidget::addBSpline);
    if(!getWorld()->getComponent<Script>(entity_).value_or(nullptr))
        menu.addAction("Script", this, &AddComponentWidget::addScript);
    if(!getWorld()->getComponent<Camera>(entity_).value_or(nullptr))
        menu.addAction("Camera", this, &AddComponentWidget::addCamera);
    if(!getWorld()->getComponent<Input>(entity_).value_or(nullptr))
        menu.addAction("Input", this, &AddComponentWidget::addInput);
    if(!getWorld()->getComponent<Light>(entity_).value_or(nullptr))
        menu.addAction("Light", this, &AddComponentWidget::addLight);
    if(!getWorld()->getComponent<Npc>(entity_).value_or(nullptr))
        menu.addAction("Npc", this, &AddComponentWidget::addNpc);
    if(!getWorld()->getComponent<Projectile>(entity_).value_or(nullptr))
        menu.addAction("Projectile", this, &AddComponentWidget::addProjectile);
    if(!getWorld()->getComponent<GUI>(entity_).value_or(nullptr))
        menu.addAction("GUI", this, &AddComponentWidget::addGUI);

    menu.exec(QCursor::pos());
}
void AddComponentWidget::addTransform()
{
    getWorld()->addComponent(entity_, Transform());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addBSpline()
{
    getWorld()->addComponent(entity_, BSpline());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addCamera()
{
    getWorld()->addComponent(entity_, Camera());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addCollision()
{
    getWorld()->addComponent(entity_, Collision());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addInput()
{
    getWorld()->addComponent(entity_, Input());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addLight()
{
    getWorld()->addComponent(entity_, Light());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addMaterial()
{
    getWorld()->addComponent(entity_, Material(ShaderManager::get()->colorShader()));
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addMesh()
{
    getWorld()->addComponent(entity_, Mesh());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addNpc()
{
    getWorld()->addComponent(entity_, Npc());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addProjectile()
{
    getWorld()->addComponent(entity_, Projectile());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addSound()
{
    getWorld()->addComponent(entity_, Sound());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addGUI()
{
    getWorld()->addComponent(entity_, GUI());
    emit updateComponentPanel(entity_);
}

void AddComponentWidget::addScript()
{
    getWorld()->addComponent(entity_, Script());
    emit updateComponentPanel(entity_);
}

#include "soundwidget.h"
#include "ui_soundwidget.h"
#include "Components/soundcomponent.h"
#include "World.h"
SoundWidget::SoundWidget(Entity entity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    Component = World::getWorld()->getComponent<Sound>(entity).value_or(nullptr);

    if(Component)
        ui->fileNameHere->setText(QString::fromStdString(Component->audio->mName));
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

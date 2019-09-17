#include "soundwidget.h"
#include "ui_soundwidget.h"
#include "resourcemanager.h"
SoundWidget::SoundWidget(unsigned int EntityID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    Component = ResourceManager::instance()->getSoundComponent(EntityID);

    ui->fileNameHere->setText(QString::fromStdString(Component->Sound.mName));
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

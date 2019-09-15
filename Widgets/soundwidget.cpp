#include "soundwidget.h"
#include "ui_soundwidget.h"
#include "resourcemanager.h"
SoundWidget::SoundWidget(unsigned int EntityID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    SoundComponent* Component;
    try {
        Component = &ResourceManager::instance()->mSoundComponents.at(EntityID);
    } catch (...) {
        auto id =  ResourceManager::instance()->mSoundMap.at(EntityID);
        Component = &ResourceManager::instance()->mSoundComponents.at(id);
    }

   ui->fileNameHere->setText(QString::fromStdString(Component->Sound.mName));
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

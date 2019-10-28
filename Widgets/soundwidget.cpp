#include "soundwidget.h"
#include "ui_soundwidget.h"
#include "Components/sound.h"
#include "world.h"
#include "Systems/soundsystem.h"
#include "soundsource.h"
SoundWidget::SoundWidget(Entity entity, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    Component = getWorld()->getComponent<Sound>(entity).value_or(nullptr);

    if(Component)
        ui->fileNameHere->setText(QString::fromStdString(Component->audio_->mName));
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

void SoundWidget::on_playButton_clicked()
{
    SoundSystem::playSound(Component);
}

void SoundWidget::on_pauseButton_clicked()
{
    SoundSystem::pauseSound(Component);
}

void SoundWidget::on_stopButton_clicked()
{
    SoundSystem::stopSound(Component);
}

#include "soundwidget.h"
#include "ui_soundwidget.h"
#include "Components/sound.h"
#include "world.h"
#include "Systems/soundsystem.h"
#include "soundsource.h"
#include <QMenu>
SoundWidget::SoundWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    Component = getWorld()->getComponent<Sound>(entity).value_or(nullptr);

    if(Component)
        ui->fileNameHere->setText(QString::fromStdString(Component->audio_->name_));
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

void SoundWidget::on_moreButton_clicked()
{
    QMenu subMenu;

    // Add actions here with name and slot to execute when action is pressed
    subMenu.addAction("Remove", this, &SoundWidget::remove);

    subMenu.exec(mapToGlobal(ui->moreButton->pos()));
}

void SoundWidget::remove()
{
    getWorld()->removeComponent<Sound>(entity_);
    hide();
}

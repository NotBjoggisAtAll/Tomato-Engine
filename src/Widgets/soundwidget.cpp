#include "soundwidget.h"
#include "ui_soundwidget.h"
#include "soundsource.h"
#include "Components/sound.h"
#include "world.h"
#include "Systems/soundsystem.h"
#include "Managers/soundmanager.h"
#include "constants.h"
#include <QMenu>
#include <QFile>

SoundWidget::SoundWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::SoundWidget)
{
    ui->setupUi(this);

    ui->gainSlider->setRange(0,100);
    ui->gainSlider->setSingleStep(1);
    component_ = getWorld()->getComponent<Sound>(entity).value_or(nullptr);

    if(component_)
    {
        if(component_->audio_)
        {
            ui->fileName->setText(QString::fromStdString(component_->audio_->file_));
            ui->loopCheckBox->setChecked(component_->audio_->bLoop_);
            ui->gainSlider->setValue(static_cast<int>(component_->audio_->gain_ * 100.f));
        }
    }
}

SoundWidget::~SoundWidget()
{
    delete ui;
}

void SoundWidget::on_playButton_clicked()
{
    SoundSystem::playSound(component_);
}

void SoundWidget::on_pauseButton_clicked()
{
    SoundSystem::pauseSound(component_);
}

void SoundWidget::on_stopButton_clicked()
{
    SoundSystem::stopSound(component_);
}

void SoundWidget::on_moreButton_clicked()
{
    QMenu subMenu;
    subMenu.addAction("Remove", this, &SoundWidget::remove);
    subMenu.exec(QCursor::pos());
}

void SoundWidget::remove()
{
    getWorld()->removeComponent<Sound>(entity_);
    hide();
}

void SoundWidget::on_fileName_editingFinished()
{
    if(!QFile::exists(QString::fromStdString(gsl::soundFilePath) + ui->fileName->text()))
    {
        ui->fileName->setStyleSheet("color: red");
        component_->audio_ = nullptr;
    }
    else
    {
        ui->fileName->setStyleSheet("");
        component_->audio_ = SoundManager::instance()->createSource(
                    ui->fileName->text().toStdString(),
                    ui->fileName->text().toStdString(),
                    ui->loopCheckBox->isChecked(),
                    static_cast<float>(ui->gainSlider->value())/100.f
                    );
    }
}

void SoundWidget::on_fileName_textEdited(const QString &/*arg1*/)
{
    ui->fileName->setStyleSheet("");
}

void SoundWidget::on_loopCheckBox_toggled(bool checked)
{
    if(component_->audio_)
        component_->audio_->setLooping(checked);
}

void SoundWidget::on_gainSlider_sliderMoved(int position)
{
    qDebug() << position;
    component_->audio_->setGain(static_cast<float>(position)/100.f);
}

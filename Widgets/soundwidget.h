#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include <QWidget>
#include "types.h"
class Sound;

namespace Ui {
class SoundWidget;
}

class SoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoundWidget(Entity entity, QWidget *parent = nullptr);
    ~SoundWidget();

private slots:
    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

private:

    Sound* Component{nullptr};

    Ui::SoundWidget *ui;
};

#endif // SOUNDWIDGET_H

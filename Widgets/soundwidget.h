#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include <QWidget>
#include "types.h"

struct Sound;

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

    void on_moreButton_clicked();

    void remove();
private:

    Sound* Component{nullptr};
    Entity entity_ = -1;
    Ui::SoundWidget *ui;
};

#endif // SOUNDWIDGET_H

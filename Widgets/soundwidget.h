#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include <QWidget>

namespace Ui {
class SoundWidget;
}

class SoundWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SoundWidget(unsigned int EntityID, QWidget *parent = nullptr);
    ~SoundWidget();

private:
    Ui::SoundWidget *ui;
};

#endif // SOUNDWIDGET_H

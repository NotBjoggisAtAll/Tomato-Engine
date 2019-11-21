#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include "types.h"

struct Input;

namespace Ui {
class InputWidget;
}

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InputWidget(Entity entity, QWidget *parent = nullptr);
    ~InputWidget();

private slots:
    void on_pushButton_clicked();

    void remove();
private:
    Entity entity_ = -1;

    Ui::InputWidget *ui;

    Input* component_ = nullptr;
};

#endif // INPUTWIDGET_H

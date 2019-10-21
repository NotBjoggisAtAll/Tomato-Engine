#ifndef ADDCOMPONENTWIDGET_H
#define ADDCOMPONENTWIDGET_H

#include <QWidget>

namespace Ui {
class AddComponentWidget;
}

class AddComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddComponentWidget(QWidget *parent = nullptr);
    ~AddComponentWidget();

private:
    Ui::AddComponentWidget *ui;
};

#endif // ADDCOMPONENTWIDGET_H

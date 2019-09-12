#ifndef MESHWIDGET_H
#define MESHWIDGET_H

#include <QWidget>

namespace Ui {
class MeshWidget;
}

class MeshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeshWidget(QWidget *parent = nullptr);
    ~MeshWidget();

private:
    Ui::MeshWidget *ui;
};

#endif // MESHWIDGET_H

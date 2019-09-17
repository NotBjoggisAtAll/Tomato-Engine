#ifndef MESHWIDGET_H
#define MESHWIDGET_H

#include <QWidget>
#include "Entity.h"

class MeshComponent;

namespace Ui {
class MeshWidget;
}

class MeshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeshWidget(Entity EntityID, QWidget *parent = nullptr);
    ~MeshWidget();

private slots:
    void on_isVisible_toggled(bool checked);

private:
    Ui::MeshWidget *ui;
    MeshComponent* Component = {nullptr};
};

#endif // MESHWIDGET_H

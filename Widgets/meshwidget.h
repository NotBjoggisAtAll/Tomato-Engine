#ifndef MESHWIDGET_H
#define MESHWIDGET_H

#include <QWidget>
#include "types.h"

class Mesh;

namespace Ui {
class MeshWidget;
}

class MeshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeshWidget(Entity entity, QWidget *parent = nullptr);
    ~MeshWidget();

private slots:
    void on_isVisible_toggled(bool checked);

private:
    Ui::MeshWidget *ui;
    Mesh* Component = {nullptr};
};

#endif // MESHWIDGET_H

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
    explicit MeshWidget(Entity entity_, QWidget *parent = nullptr);
    ~MeshWidget();

private slots:
    void on_isVisible_toggled(bool checked);

    void on_changeMeshButton_clicked();

    void showContextMenu(const QPoint &point);
    void remove();
private:
    Ui::MeshWidget *ui;
    Mesh* Component = nullptr;
    Entity entity_ = -1;
};

#endif // MESHWIDGET_H

#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>
#include "types.h"
#include <memory>

struct Transform;

namespace Ui {
class TransformWidget;
}

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(Entity entityIn, QWidget *parent = nullptr);
    ~TransformWidget();

private slots:

    void on_xPosition_valueChanged(double arg1);

    void on_yPosition_valueChanged(double arg1);

    void on_zPosition_valueChanged(double arg1);

    void on_xRotation_valueChanged(double arg1);

    void on_yRotation_valueChanged(double arg1);

    void on_zRotation_valueChanged(double arg1);

    void on_xScale_valueChanged(double arg1);

    void on_yScale_valueChanged(double arg1);

    void on_zScale_valueChanged(double arg1);

    void on_pushButton_clicked();

    void resetToDefault();
    void remove();
private:
    Ui::TransformWidget *ui;
    Entity entity_;
    Transform* Component {nullptr};

    bool initDone = false;
};

#endif // TRANSFORMWIDGET_H

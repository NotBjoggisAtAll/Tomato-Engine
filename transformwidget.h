#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>

class TransformComponent;

namespace Ui {
class TransformWidget;
}

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(QWidget *parent = nullptr);
    ~TransformWidget();

    void setup(unsigned int EntityID);
private slots:
    void on_xDoubleSpinBox_valueChanged(double arg1);

    void on_yDoubleSpinBox_valueChanged(double arg1);

    void on_zDoubleSpinBox_valueChanged(double arg1);

private:
    Ui::TransformWidget *ui;

    TransformComponent* Transform {nullptr};
};

#endif // TRANSFORMWIDGET_H

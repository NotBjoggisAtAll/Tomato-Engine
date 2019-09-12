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
    explicit TransformWidget(unsigned int &EntityID, QWidget *parent = nullptr);
    ~TransformWidget();

private slots:

    void on_xPosition_valueChanged(double arg1);

    void on_yPosition_valueChanged(double arg1);

    void on_zPosition_valueChanged(double arg1);

private:
    Ui::TransformWidget *ui;

    TransformComponent* Component {nullptr};
};

#endif // TRANSFORMWIDGET_H

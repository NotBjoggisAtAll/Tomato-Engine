#ifndef VECTOR3DPICKER_H
#define VECTOR3DPICKER_H

#include "GSL/vector3d.h"
#include <QDialog>

namespace Ui {
class Vector3DPicker;
}

class Vector3DPicker : public QDialog
{
    Q_OBJECT

public:
    explicit Vector3DPicker(QWidget *parent = nullptr);
    ~Vector3DPicker();

signals:
    void sendVector3D(gsl::Vector3D);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Vector3DPicker *ui;
};

#endif // VECTOR3DPICKER_H

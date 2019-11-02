#include "vector3dpicker.h"
#include "ui_vector3dpicker.h"

Vector3DPicker::Vector3DPicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Vector3DPicker)
{
    ui->setupUi(this);
}

Vector3DPicker::~Vector3DPicker()
{
    delete ui;
}

void Vector3DPicker::on_buttonBox_accepted()
{
    emit sendVector3D(gsl::Vector3D(
                          static_cast<float>(ui->x->text().toDouble()),
                          static_cast<float>(ui->y->text().toDouble()),
                          static_cast<float>(ui->z->text().toDouble())));
}

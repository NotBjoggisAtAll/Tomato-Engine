#include "meshwidget.h"
#include "ui_meshwidget.h"

MeshWidget::MeshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshWidget)
{
    ui->setupUi(this);
}

MeshWidget::~MeshWidget()
{
    delete ui;
}

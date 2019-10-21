#include "addcomponentwidget.h"
#include "ui_addcomponentwidget.h"

AddComponentWidget::AddComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddComponentWidget)
{
    ui->setupUi(this);
}

AddComponentWidget::~AddComponentWidget()
{
    delete ui;
}

#include "inputwidget.h"
#include "ui_inputwidget.h"
#include "Components/input.h"
#include "world.h"
#include <QMenu>

InputWidget::InputWidget(Entity entity, QWidget *parent) :
    QWidget(parent), entity_(entity),
    ui(new Ui::InputWidget)
{
    ui->setupUi(this);
    component_ = getWorld()->getComponent<Input>(entity_).value();
}

InputWidget::~InputWidget()
{
    delete ui;
}

void InputWidget::on_pushButton_clicked()
{
    QMenu subMenu;
    subMenu.addAction("Remove", this, &InputWidget::remove);
    subMenu.exec(QCursor::pos());
}

void InputWidget::remove()
{
    getWorld()->removeComponent<Input>(entity_);
    hide();
}

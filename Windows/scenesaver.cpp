#include "scenesaver.h"
#include "ui_scenesaver.h"
#include "constants.h"
#include <QFile>
SceneSaver::SceneSaver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneSaver)
{
    ui->setupUi(this);
    setWindowTitle("Create new Scene");
}

SceneSaver::~SceneSaver()
{
    delete ui;
}

void SceneSaver::on_buttonBox_accepted()
{
    emit onSave(ui->newSceneName->text());
}

#include "loadscene.h"
#include "ui_loadscene.h"
#include "constants.h"
#include <QFile>
#include <QDirIterator>
#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include "mainwindow.h"
LoadScene::LoadScene(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadScene)
{
    ui->setupUi(this);

    //    QDir directory (QString::fromStdString(gsl::jsonFilePath));
    //    qDebug() << directory.entryList();

    QDirIterator dirIterator(QString::fromStdString(gsl::jsonFilePath), QDir::AllEntries | QDir::NoDotAndDotDot);
    while(dirIterator.hasNext())
    {
        dirIterator.next();
        QFileInfo info(dirIterator.filePath());
        if(info.isFile())
            ui->jsonList->addItem(info.baseName());
    }

}

LoadScene::~LoadScene()
{
    delete ui;
}

void LoadScene::on_buttonBox_accepted()
{
    MainWindow* w = new MainWindow(ui->jsonList->currentItem()->text() + ".json");
    w->show();
}

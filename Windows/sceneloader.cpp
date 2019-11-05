#include "sceneloader.h"
#include "ui_sceneloader.h"
#include "constants.h"
#include <QDirIterator>
#include <QListWidgetItem>
#include <QFileInfo>
#include "mainwindow.h"

SceneLoader::SceneLoader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadScene)
{
    ui->setupUi(this);

    setWindowTitle("Scene Loader");

    QDirIterator dirIterator(QString::fromStdString(gsl::jsonFilePath), QDir::AllEntries | QDir::NoDotAndDotDot);
    while(dirIterator.hasNext())
    {
        dirIterator.next();
        QFileInfo info(dirIterator.filePath());
        if(info.isFile())
            ui->jsonList->addItem(info.baseName());
    }
}

SceneLoader::~SceneLoader()
{
    delete ui;
}

void SceneLoader::on_buttonBox_accepted()
{
    emit onLoad(ui->jsonList->currentItem()->text());
}

void SceneLoader::on_jsonList_itemDoubleClicked(QListWidgetItem *item)
{
    emit onLoad(item->text());
    close();
}

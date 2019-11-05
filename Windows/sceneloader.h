#ifndef LOADSCENE_H
#define LOADSCENE_H

#include <QDialog>

namespace Ui {
class loadScene;
}

class QListWidgetItem;

class SceneLoader : public QDialog
{
    Q_OBJECT

public:
    explicit SceneLoader(QWidget *parent = nullptr);
    ~SceneLoader();

signals:
    void onLoad(QString);

private slots:
    void on_buttonBox_accepted();

    void on_jsonList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::loadScene *ui;


};

#endif // LOADSCENE_H

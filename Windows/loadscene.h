#ifndef LOADSCENE_H
#define LOADSCENE_H

#include <QDialog>

namespace Ui {
class loadScene;
}

class LoadScene : public QDialog
{
    Q_OBJECT

public:
    explicit LoadScene(QWidget *parent = nullptr);
    ~LoadScene();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::loadScene *ui;
};

#endif // LOADSCENE_H

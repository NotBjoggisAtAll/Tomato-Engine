#ifndef SCENESAVER_H
#define SCENESAVER_H

#include <QDialog>

namespace Ui {
class SceneSaver;
}

class SceneSaver : public QDialog
{
    Q_OBJECT

public:
    explicit SceneSaver(QWidget *parent = nullptr);
    ~SceneSaver();

signals:
    void onSave(QString);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::SceneSaver *ui;
};

#endif // SCENESAVER_H

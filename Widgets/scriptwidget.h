#ifndef SCRIPTWIDGET_H
#define SCRIPTWIDGET_H

#include <QWidget>
#include "types.h"

class Script;

namespace Ui {
class ScriptWidget;
}

class ScriptWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptWidget(Entity entity, QWidget *parent = nullptr);
    ~ScriptWidget();

private slots:
    void on_moreButton_clicked();

    void remove();

    /*
     * Tries to open the file with their default editor program.
     * If the file doesnt exist it creates a file with that name
     * and then opens it.
     */
    void on_openFileButton_clicked();

    void on_filePathText_editingFinished();

private:
    Entity entity_ = -1;
    Script* component_ = nullptr;

    Ui::ScriptWidget *ui;
};

#endif // SCRIPTWIDGET_H

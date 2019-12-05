#ifndef MATERIALWIDGET_H
#define MATERIALWIDGET_H

#include <QWidget>
#include "types.h"

struct Material;

namespace Ui {
class MaterialWidget;
}

class MaterialWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialWidget(Entity entity, QWidget *parent = nullptr);
    ~MaterialWidget();

private slots:
    void on_pushButton_clicked();

    void remove();

    void on_rColor_valueChanged(double arg1);

    void on_gColor_valueChanged(double arg1);

    void on_bColor_valueChanged(double arg1);

    void on_shaderBox_currentIndexChanged(const QString &arg1);

    void on_textureName_editingFinished();

    void on_textureName_textEdited(const QString &);

private:

    Material* component_ = nullptr;

    Entity entity_ = -1;

    Ui::MaterialWidget *ui;
};

#endif // MATERIALWIDGET_H

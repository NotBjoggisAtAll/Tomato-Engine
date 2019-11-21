#ifndef PROJECTILEWIDGET_H
#define PROJECTILEWIDGET_H

#include <QWidget>
#include "types.h"

struct Projectile;

namespace Ui {
class ProjectileWidget;
}

class ProjectileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectileWidget(Entity entity, QWidget *parent = nullptr);
    ~ProjectileWidget();

private slots:
    void on_speedSpinBox_valueChanged(double arg1);

    void on_lifeTimeSpinBox_valueChanged(double arg1);

    void on_moreButton_clicked();

    void remove();
    void resetToDefault();
private:
    Entity entity_ = -1;
    Projectile* component_ = nullptr;
    Ui::ProjectileWidget *ui;
};

#endif // PROJECTILEWIDGET_H

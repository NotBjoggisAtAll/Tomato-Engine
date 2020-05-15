#ifndef PROJECTILEWIDGET_H
#define PROJECTILEWIDGET_H

#include <QWidget>
#include "types.h"

struct Projectile;

namespace Ui {
class ProjectileWidget;
}

/**
 * The ProjectileWidget shows the Projectile component in the editor.
 */
class ProjectileWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit ProjectileWidget(Entity entity, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~ProjectileWidget();

private slots:
    /**
      * Called when the Doublespinbox speedSpinBox is changed.
      * Updates the component speed based on what arg1 is.
      * @param arg1 - double.
      */
    void on_speedSpinBox_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox lifeTimeSpinBox is changed.
      * Updates the component lifetime based on what arg1 is.
      * @param arg1 - double.
      */
    void on_lifeTimeSpinBox_valueChanged(double arg1);

    /**
     * Called when clicked Reset To Default inside the options menu.
     * Resets the component to default values.
     */
    void reset();

    /**
     * Called when the "..." button is pressed.
     * Used to show a menu of options.
     */
    void on_moreButton_clicked();

    /**
     * Called when clicked on Remove inside the options menu.
     * Removes the component from the entity.
     */
    void remove();
private:
    /// The entity  this ProjectileWidget is made for.
    Entity entity_ = -1;

    ///The Projectile component of the entity.
    Projectile* component_ = nullptr;

    Ui::ProjectileWidget *ui;
};

#endif // PROJECTILEWIDGET_H

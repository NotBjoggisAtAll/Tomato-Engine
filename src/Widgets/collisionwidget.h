#ifndef COLLISIONWIDGET_H
#define COLLISIONWIDGET_H

#include <QWidget>
#include "types.h"

struct Collision;

namespace Ui {
class CollisionWidget;
}

/**
 * The CollisionWidget shows the Collision component in the editor.
 */
class CollisionWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit CollisionWidget(Entity entity, QWidget *parent = nullptr);
    /**
     * Default deconstructor.
     */
    ~CollisionWidget();

private slots:
    /**
     * Called when the "..." button is pressed.
     * Used to show a menu of options.
     */
    void on_pushButton_clicked();
    /**
     * Called when clicked on Remove inside the options menu.
     * Removes the component from the entity.
     */
    void remove();

    /**
     * Called when clicked on Update from Mesh inside the options menu.
     * Updates the collision component with data from a Mesh component with the same file/object name.
     */
    void updateWidget();

    /**
      * Called when the Doublespinbox xMin is changed.
      * Updates the component collision based on what arg1 is.
      * @param arg1 - double.
      */
    void on_xMin_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox yMin is changed.
      * Updates the component collision based on what arg1 is.
      * @param arg1 - double.
      */
    void on_yMin_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox zMin is changed.
      * Updates the component collision based on what arg1 is.
      * @param arg1 - double.
      */
    void on_zMin_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox xMax is changed.
      * Updates the component collision based on what arg1 is.
      * @param arg1 - double.
      */
    void on_xMax_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox yMax is changed.
      * Updates the component collision based on what arg1 is.
      * @param arg1 - double.
      */
    void on_yMax_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox zMax is changed.
      * Updates the component collision based on what arg1 is.
      * @param arg1 - double.
      */
    void on_zMax_valueChanged(double arg1);

private:
    /// The Collision component of the entity.
    Collision* component_ = nullptr;
    /// The entity this CollisionWidget is made for.
    Entity entity_ = -1;

    Ui::CollisionWidget *ui;
};

#endif // COLLISIONWIDGET_H

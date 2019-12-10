#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>
#include "types.h"
#include <memory>
#include "GSL/vector3d.h"

struct Transform;

namespace Ui {
class TransformWidget;
}
/**
 * The TransformWidget shows the Transform component in the editor.
 */
class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit TransformWidget(Entity entityIn, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~TransformWidget();

private slots:

    /**
      * Called when the Doublespinbox xPosition is changed.
      * Updates the components position based on what arg1 is.
      * @param arg1 - double.
      */
    void on_xPosition_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox yPosition is changed.
      * Updates the components position based on what arg1 is.
      * @param arg1 - double.
      */
    void on_yPosition_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox zPosition is changed.
      * Updates the components position based on what arg1 is.
      * @param arg1 - double.
      */
    void on_zPosition_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox xRotation is changed.
      * Updates the components rotation based on what arg1 is.
      * @param arg1 - double.
      */
    void on_xRotation_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox yRotation is changed.
      * Updates the components rotation based on what arg1 is.
      * @param arg1 - double.
      */
    void on_yRotation_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox zRotation is changed.
      * Updates the components rotation based on what arg1 is.
      * @param arg1 - double.
      */
    void on_zRotation_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox xScale is changed.
      * Updates the components scale based on what arg1 is.
      * @param arg1 - double.
      */
    void on_xScale_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox yScale is changed.
      * Updates the components scale based on what arg1 is.
      * @param arg1 - double.
      */
    void on_yScale_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox zScale is changed.
      * Updates the components scale based on what arg1 is.
      * @param arg1 - double.
      */
    void on_zScale_valueChanged(double arg1);

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
     * Called when clicked Reset To Default inside the options menu.
     * Resets the component to default values.
     */
    void reset();

private:
    Ui::TransformWidget *ui;

    /**
     * Translates the entity's position based on the parameter.
     * Also updates the entity's children.
     * @param entity - Entity
     * @param translation - gsl::Vector3D.
     */
    void addPosition(Entity entity, gsl::Vector3D translation);

    /**
     * Sets the entity's position based on the parameter.
     * Also updates the entity's children.
     * @param entity - Entity.
     * @param position - gsl::Vector3D.
     */
    void setPosition(Entity entity, gsl::Vector3D position);

    /**
     * Sets the entity's scale based on the parameter.
     * Also updates the entity's children.
     * @param entity - Entity.
     * @param scale - gsl::Vector3D.
     */
    void setScale(Entity entity, gsl::Vector3D scale);

    /// The Entity this TransformWidget was made for.
    Entity entity_ = -1;

    /// The Transform component of the entity.
    Transform* component_ = nullptr;

    /// Is true when init(constructor is done). Used so the doublespinbox value changed functions isnt called while filling up default values.
    bool initDone = false;
};

#endif // TRANSFORMWIDGET_H

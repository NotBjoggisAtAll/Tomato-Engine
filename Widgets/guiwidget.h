#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include <QWidget>
#include "types.h"

class GUI;

namespace Ui {
class GUIWidget;
}

/**
 * The GUIWidget shows the GUI component in the editor.
 */
class GUIWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit GUIWidget(Entity entity, QWidget *parent = nullptr);
    /**
     * Default deconstructor.
     */
    ~GUIWidget();

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
     * Called when clicked Reset To Default inside the options menu.
     * Resets the component to default values.
     */
    void reset();

    /**
     * Called when the Doublespinbox xPos is changed.
     * Updates the components position based on what arg1 is.
     * @param arg1 - double.
     */
    void on_xPos_valueChanged(double arg1);

    /**
     * Called when the Doublespinbox yPos is changed.
     * Updates the components position based on what arg1 is.
     * @param arg1 - double.
     */
    void on_yPos_valueChanged(double arg1);

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

private:
    /// The GUI component of the entity.
    GUI* component_ = nullptr;
    /// The entity this GUIWidget is made for.
    Entity entity_ = -1;

    Ui::GUIWidget *ui;
};

#endif // GUIWIDGET_H

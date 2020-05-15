#ifndef BSPLINEWIDGET_H
#define BSPLINEWIDGET_H

#include <QWidget>
#include "types.h"
#include "GSL/vector3d.h"

struct BSpline;
class Vector3DPicker;

namespace Ui {
class BSplineWidget;
}

/**
* The BSplineWidget shows the BSpline component in the editor.
*/
class BSplineWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit BSplineWidget(Entity entity, QWidget *parent = nullptr);
    /**
     * Default deconstructor.
     */
    ~BSplineWidget();

private slots:

    /**
     * Called when the button addPoint is clicked.
     * Opens the Vector3DPicker.
     */
    void on_addPoint_clicked();

    /**
     * Called when the button removePoint is clicked.
     * Removes the point from the component and from the UI list.
     */
    void on_removePoint_clicked();

    /**
     * Called when the user has closed the Vector3DPicker.
     * Adds a new point in the component and in the UI list.
     * @param vector - gsl::Vector3D. The new point to add.
     */
    void vector3DRecieved(gsl::Vector3D vector);

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
    /// The BSpline component of the entity.
    BSpline* component_ = nullptr;
    /// The entity this BSplineWidget is made for.
    Entity entity_ = -1;
    /// A Vector3DPicker. Used to make new points in the BSpline.
    Vector3DPicker* vector3DPicker_ = nullptr;

    Ui::BSplineWidget *ui;
};

#endif // BSPLINEWIDGET_H

#ifndef VECTOR3DPICKER_H
#define VECTOR3DPICKER_H

#include "GSL/vector3d.h"
#include <QDialog>

namespace Ui {
class Vector3DPicker;
}

/**
 * The Vector3DPicker is a custom dialog window used to create a point when working with BSplines in the editor.
 */
class Vector3DPicker : public QDialog
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * @param windowTitle - The window title.
     * @param parent - The parent of this Picker.
     */
    explicit Vector3DPicker(QString windowTitle, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~Vector3DPicker();

signals:
    /**
     * The signal is emitted when the user presses OK in the dialog window. Sends the vector to the BSplineWidget.
     */
    void sendVector3D(gsl::Vector3D);

private slots:

    /**
     * Called when the user presses the OK button. Calls the signal sendVector3D.
     */
    void on_buttonBox_accepted();

private:
    Ui::Vector3DPicker *ui;
};

#endif // VECTOR3DPICKER_H

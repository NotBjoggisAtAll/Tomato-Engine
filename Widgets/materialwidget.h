#ifndef MATERIALWIDGET_H
#define MATERIALWIDGET_H

#include <QWidget>
#include "types.h"

struct Material;

namespace Ui {
class MaterialWidget;
}

/**
 * The MaterialWidget shows the Material component in the editor.
 */
class MaterialWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit MaterialWidget(Entity entity, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~MaterialWidget();

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
      * Called when the Doublespinbox rColor is changed.
      * Updates the component color based on what arg1 is.
      * @param arg1 - double.
      */
    void on_rColor_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox gColor is changed.
      * Updates the component color based on what arg1 is.
      * @param arg1 - double.
      */
    void on_gColor_valueChanged(double arg1);

    /**
      * Called when the Doublespinbox bColor is changed.
      * Updates the component color based on what arg1 is.
      * @param arg1 - double.
      */
    void on_bColor_valueChanged(double arg1);

    /**
     * Called when the comboBox shaderBox is changed.
     * Updated the component shader based on what arg1 is.
     * @param arg1
     */
    void on_shaderBox_currentIndexChanged(const QString &arg1);

    /**
     * Called when the user has stopped editing the lineEdit textureName.
     * If the texture file is valid the component is updated with that texture.
     * If not the text turns red and nothing is changed.
     */
    void on_textureName_editingFinished();

    /**
     * Called whenever the use edit text in the lineEdit textureName.
     * Used to turn the color back to black while writing after an invalid file.
     */
    void on_textureName_textEdited(const QString &);

private:
    /// The Material component of the entity.
    Material* component_ = nullptr;

    /// The entity this MaterialWidget is made for.
    Entity entity_ = -1;

    Ui::MaterialWidget *ui;
};

#endif // MATERIALWIDGET_H

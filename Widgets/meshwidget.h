#ifndef MESHWIDGET_H
#define MESHWIDGET_H

#include <QWidget>
#include "types.h"

struct Mesh;

namespace Ui {
class MeshWidget;
}

/**
 * The MeshWidget shows the Mesh component in the editor.
 */
class MeshWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit MeshWidget(Entity entity_, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~MeshWidget();

private slots:
    /**
     * Called when the Visible check box is changed.
     * Updates the Mesh component with if it should be visible or not.
     * @param checked - bool.
     */
    void on_isVisible_toggled(bool checked);

    /**
     * Called when the Change Mesh button is pressed.
     * Opens a filedialog so the user can pick a file to load.
     * Loads the file and replaces the current Mesh with the new one.
     */
    void on_changeMeshButton_clicked();

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
    Ui::MeshWidget *ui;

    /// The Mesh component of the entity.
    Mesh* component_ = nullptr;

    /// The entity this MeshWidget is made for.
    Entity entity_ = -1;
};

#endif // MESHWIDGET_H

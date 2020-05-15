#ifndef SCRIPTWIDGET_H
#define SCRIPTWIDGET_H

#include <QWidget>
#include "types.h"

struct Script;

namespace Ui {
class ScriptWidget;
}
/**
 * The ScriptWidget shows the Scrip component in the editor.
 */
class ScriptWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit ScriptWidget(Entity entity, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~ScriptWidget();

private slots:
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

    /**
     * Called when the openFile button is pressed.
     * Tries to open the file with their default editor program.
     * If the file doesnt exist it creates a file with that name
     * and then opens it.
     */
    void on_openFileButton_clicked();

    /**
     * Called when the filePathText is done being edited.
     * Updates the component filepath variable to the text inside the filePathText.
     */
    void on_filePathText_editingFinished();

private:
    /// The entity this ScriptWidget is made for.
    Entity entity_ = -1;
    /// The Script component of the entity.
    Script* component_ = nullptr;

    Ui::ScriptWidget *ui;
};

#endif // SCRIPTWIDGET_H

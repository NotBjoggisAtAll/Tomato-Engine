#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include "types.h"

struct Input;

namespace Ui {
class InputWidget;
}
/**
 * The InputWidget shows the Input component in the editor.
 */
class InputWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in a entity when created.
     * @param entity - Entity.
     */
    explicit InputWidget(Entity entity, QWidget *parent = nullptr);
    /**
     * Default deconstructor.
     */
    ~InputWidget();

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
private:
    /// The Input component of the entity.
    Input* component_ = nullptr;
    /// The entity this InputWidget is made for.
    Entity entity_ = -1;
    Ui::InputWidget *ui;
};

#endif // INPUTWIDGET_H

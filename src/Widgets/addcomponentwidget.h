#ifndef ADDCOMPONENTWIDGET_H
#define ADDCOMPONENTWIDGET_H

#include <QWidget>
#include "types.h"

class QMenu;

namespace Ui {
class AddComponentWidget;
}
/**
 * The AddComponentWidget is used to add components to an entity in the editor.
 * You can only add the same type of component once.
 */
class AddComponentWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit AddComponentWidget(Entity entity, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~AddComponentWidget();

private slots:

    /**
     * Called when the button addButton is clicked.
     * Constructs and shows a menu of all available components to add.
     */
    void on_addButton_clicked();

    /**
     * Called when clicked on Transform inside the add menu.
     * Adds the component to the entity.
     */
    void addTransform();

    /**
     * Called when clicked on BSpline inside the add menu.
     * Adds the component to the entity.
     */
    void addBSpline();

    /**
     * Called when clicked on Camera inside the add menu.
     * Adds the component to the entity.
     */
    void addCamera();

    /**
     * Called when clicked on Collision inside the add menu.
     * Adds the component to the entity.
     */
    void addCollision();

    /**
     * Called when clicked on Input inside the add menu.
     * Adds the component to the entity.
     */
    void addInput();

    /**
     * Called when clicked on Light inside the add menu.
     * Adds the component to the entity.
     */
    void addLight();

    /**
     * Called when clicked on Material inside the add menu.
     * Adds the component to the entity.
     */
    void addMaterial();

    /**
     * Called when clicked on Mesh inside the add menu.
     * Adds the component to the entity.
     */
    void addMesh();

    /**
     * Called when clicked on Npc inside the add menu.
     * Adds the component to the entity.
     */
    void addNpc();

    /**
     * Called when clicked on Projectile inside the add menu.
     * Adds the component to the entity.
     */
    void addProjectile();

    /**
     * Called when clicked on Sound inside the add menu.
     * Adds the component to the entity.
     */
    void addSound();

    /**
     * Called when clicked on GUI inside the add menu.
     * Adds the component to the entity.
     */
    void addGUI();

    void addScript();
signals:

    /**
     * Emitted when a component is added.
     * Updates the component panel so the new component added is visible in the editor.
     * @param entity - Entity.
     */
    void updateComponentPanel(Entity entity);

private:
    /// The entity this AddComponentWidget is made for.
    Entity entity_ = -1;

    Ui::AddComponentWidget *ui;
};

#endif // ADDCOMPONENTWIDGET_H

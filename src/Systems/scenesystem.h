#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "system.h"
#include <QJsonObject>
#include <QFileInfo>
#include <unordered_map>
#include "Components/camera.h"
#include "Components/transform.h"

/**
 * Used to store the EditorCamera while playing the game.
 */
struct EditorCamera
{
    /// The Camera component.
    Camera camera_;

    /// The Transform component.
    Transform transform_;
};

/**
 * The SceneSystem is responsible for saving and loading scenes.
 * It is used when pressing play to store the scene as a temp scene, so it can restore to it when the game is over.
 * Also is used to save and load scenes while editing, so you can return back to the scene at a later point.
 * Saves the scenes as a JSON file.
 */
class SceneSystem : public System
{
public:
    /**
     * Default constructor.
     */
    SceneSystem() = default;

    /**
     * BeginPlay runs when the the actual game starts.
     * Saves a temp scene to store the states of all entities before the game starts.
     */
    void beginPlay() override;

    /**
     * EndPlay runs when the game ends and goes back to the editor.
     * Restores the saved temp scene to restore the states of all entities.
     */
    void endPlay() override;

    /**
     * Used to delete all entities in the scene. Useful when you want to load a new scene or start a blank one.
     */
    void clearScene();

    /**
     * Used to load a JsonScene from a JSON file.
     * @param scene - The filepath to the JSON file.
     */
    void loadScene(QFileInfo scene);

    /**
     * Used to save a JsonScene to a JSON file.
     * @param scene - The filepath to the JSON file.
     */
    void saveScene(QFileInfo scene);

private:

    void p_loadScene(QString sceneName);

    EditorCamera editorCamera_;   ///Stores the editorcamera here while playing so I can load it back again when I stop playing.


};

#endif // SCENESYSTEM_H

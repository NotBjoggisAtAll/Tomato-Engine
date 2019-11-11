#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "system.h"
#include <QJsonObject>
#include <unordered_map>
#include "Components/camera.h"
#include "Components/transform.h"

struct EditorCamera
{
    Camera camera_;
    Transform transform_;
};

class SceneSystem : public System
{
public:

    SceneSystem();
    void beginPlay() override;
    void tick() override;
    void endPlay() override;

    void clearScene();
    void loadScene(QString sceneName);
    void saveScene(QString sceneName);

private:

    void loadScenePriv(QString sceneName);

    EditorCamera editorCamera_;   ///Stores the editorcamera here while playing so I can load it back again when I stop playing.


};

#endif // SCENESYSTEM_H

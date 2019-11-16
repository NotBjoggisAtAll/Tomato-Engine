#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "system.h"
#include <QJsonObject>
#include <QFileInfo>
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
    void tick(float deltaTime) override;
    void endPlay() override;

    void clearScene();
    void loadScene(QFileInfo scene);
    void saveScene(QFileInfo scene);

private:

    void loadScenePriv(QString sceneName);

    EditorCamera editorCamera_;   ///Stores the editorcamera here while playing so I can load it back again when I stop playing.


};

#endif // SCENESYSTEM_H

#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "system.h"
#include <QJsonObject>
#include <unordered_map>

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

    QString currentScene_ = "";

};

#endif // SCENESYSTEM_H

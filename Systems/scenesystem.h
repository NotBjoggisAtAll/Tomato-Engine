#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "system.h"
#include <QJsonObject>
#include <unordered_map>

class SceneSystem : public System
{
public:

    SceneSystem();
    void loadScene(QString sceneName);
    void saveScene(QString sceneName);

private:

    void clearScene();

};

#endif // SCENESYSTEM_H

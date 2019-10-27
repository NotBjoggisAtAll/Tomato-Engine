#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "system.h"
#include <QJsonObject>
#include <unordered_map>

class SceneSystem : public System
{
public:

    SceneSystem();
    void loadScene(QString filepath);


private:

    void clearScene();

};

#endif // SCENESYSTEM_H

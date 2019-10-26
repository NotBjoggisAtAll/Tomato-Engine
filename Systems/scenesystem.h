#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include "system.h"
#include <QJsonObject>
#include <unordered_map>

class SceneSystem : public System
{
public:

    SceneSystem();
    void loadScene(QJsonObject JSON);


private:

    void clearScene();

    std::string findComponentNameByValue(std::unordered_map<std::string, ComponentType> &ComponentTypes, ComponentType TypeToFind);
};

#endif // SCENESYSTEM_H

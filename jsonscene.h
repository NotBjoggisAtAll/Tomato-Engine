#ifndef JSONSCENE_H
#define JSONSCENE_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include "types.h"

class Camera;
namespace jba {

class JsonScene
{
public:
    JsonScene(QString SceneName);

    void makeFile(QString sceneName, bool overwrite = false);
    void addObject(Entity entity);
    void addCamera(Camera* Camera);

private:

    QJsonObject sceneObject_ = QJsonObject();
    QJsonArray entities_ = QJsonArray();
    QJsonArray cameras_ = QJsonArray();

};
}
#endif // JSONSCENE_H

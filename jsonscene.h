#ifndef JSONSCENE_H
#define JSONSCENE_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include "types.h"

namespace jba {

class JsonScene
{
public:
    JsonScene(QString SceneName);

    void makeFile(QString sceneName, bool overwrite = false);
    void makeTempFile(QString sceneName);
    void addObject(Entity entity);
private:

    QJsonObject sceneObject_ = QJsonObject();
    QJsonArray entities_ = QJsonArray();

};
}
#endif // JSONSCENE_H

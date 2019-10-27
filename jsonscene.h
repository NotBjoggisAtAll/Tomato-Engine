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

    void makeFile(QString FilePath, bool overwrite);
    void addObject(Entity entity);

private:

    QJsonObject sceneObject_ = QJsonObject();
    QJsonArray entities_ = QJsonArray();

};
}
#endif // JSONSCENE_H

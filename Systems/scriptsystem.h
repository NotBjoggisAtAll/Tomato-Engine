#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "Systems/system.h"
#include <QJsonValue>
#include <QJsonObject>

class Script;
class QJSEngine;

class ScriptSystem : public System
{
    Q_OBJECT
public:
    ScriptSystem();
    void componentAdded(Script* script);
    ~ScriptSystem() override;
    void beginPlay() override;
    void tick() override;
public slots:

    int createEntity();

    QJsonValue getComponent(QString name, int entity);
    void setComponent(QString name, int entity, QJsonObject Json);
private:
    void call(Script *script, QString function);
};

#endif // SCRIPTSYSTEM_H

#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "Systems/system.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJSValue>

class Script;

class QJSEngine;

class ScriptSystem : public System
{
    Q_OBJECT
public:
    ScriptSystem();
    void componentAdded(Script* script, Entity entity);
    ~ScriptSystem() override;
    void beginPlay() override;
    void tick() override;
    void call(Script *script, QString function);
public slots:

    int createEntity();
    void spawnEnemy(int owner);

    QJsonValue getComponent(QString name, int entity);
    void setComponent(QString name, int entity, QJsonObject Json);
private slots:
private:
    void load(Script *script);

    // System interface
public:
    virtual void endPlay() override;
};

#endif // SCRIPTSYSTEM_H

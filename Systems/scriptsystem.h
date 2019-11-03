#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "Systems/system.h"

class Script;
class QJSEngine;

class ScriptSystem : public System
{
    Q_OBJECT
public:
    ScriptSystem();
    void componentAdded(Script* script);
    ~ScriptSystem() override;
public slots:
    void beginPlay() override;
    void tick() override;

    int createEntity();

private:
    void call(Script *script, QString function);
};

#endif // SCRIPTSYSTEM_H

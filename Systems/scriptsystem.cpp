#include "scriptsystem.h"
#include <QDebug>
#include "Components/allcomponents.h"
#include "world.h"
#include "constants.h"
#include <QFile>
#include "resourcefactory.h"
#include "Managers/shadermanager.h"
#include "Script/jstimer.h"

ScriptSystem::ScriptSystem()
{

}
ScriptSystem::~ScriptSystem()
{

}
void ScriptSystem::beginPlay()
{
    for(auto entity : entities_)
    {
        auto scriptComp = getWorld()->getComponent<Script>(entity).value_or(nullptr);
        if(!scriptComp)
            continue;
        componentAdded(scriptComp, entity);
        load(scriptComp);
        call(scriptComp, "beginPlay");
    }
}

void ScriptSystem::tick()
{
    for(auto entity : entities_)
    {
        auto scriptComp = getWorld()->getComponent<Script>(entity).value_or(nullptr);
        if(!scriptComp)
            continue;
        call(scriptComp, "tick");
    }
}

void ScriptSystem::endPlay()
{
    for(auto entity : entities_)
    {
        auto scriptComp = getWorld()->getComponent<Script>(entity).value_or(nullptr);
        if(!scriptComp)
            continue;
        call(scriptComp, "endPlay");
    }
}

int ScriptSystem::createEntity()
{
    return getWorld()->createEntity();
}

void ScriptSystem::spawnEnemy(int owner)
{
    Entity entity = getWorld()->createEntity();
    getWorld()->addComponent<Transform>(entity, Transform({},{},{0.2f,0.2f,0.2f}));
    getWorld()->addComponent<Mesh>(entity, ResourceFactory::get()->loadMesh("camera.obj"));
    getWorld()->addComponent<Collision>(entity, ResourceFactory::get()->getCollision("camera.obj"));
    getWorld()->addComponent<Material>(entity, Material(ShaderManager::instance()->colorShader(),{1,0,0}));
    getWorld()->addComponent<Npc>(entity, Npc(&getWorld()->getComponent<BSpline>(owner).value()->curve_));
    qDebug() << "Spawn enemy from script";

}

QJsonValue ScriptSystem::getComponent(QString name , int entity)
{
    if(name == "Transform")
    {
        auto ptr = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        if(ptr)
            return ptr->toJson();
    }
    return 0;
}

void ScriptSystem::setComponent(QString name, int entity, QJsonObject Json)
{
    if(name == "Transform")
    {
        auto ptr = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        if(ptr)
            ptr->fromJson(Json);
    }
}

void ScriptSystem::componentAdded(Script *script, Entity entity)
{
    if(!script)
        return;

    script->engine_->globalObject().setProperty("engine", script->engine_->newQObject(this));
    script->engine_->globalObject().setProperty("id", entity);
    script->engine_->globalObject().setProperty("timer", script->engine_->newQObject(new JSTimer(entity,this)));

}

void ScriptSystem::load(Script* script)
{
    if(!script || !script->engine_ || !script->file_.size())
        return;


    QFile file(QString::fromStdString(gsl::scriptFilePath) + script->file_);
    file.open(QFile::ReadOnly);

    QTextStream stream(&file);
    QString string = stream.readAll();

    QJSValue value = script->engine_->evaluate(string, QString::fromStdString(gsl::scriptFilePath) + script->file_);
    if(value.isError())
    {
        QString lineNumber = QString::number(value.property("lineNumber").toInt());
        QString evaluationString = value.toString();
        QString error("Uncaught exception at line" + lineNumber  + ":" + evaluationString );
        qDebug() << error;
        return;
    }
}

void ScriptSystem::call(Script * script, QString function)
{
    if(!script || !function.size() || !script->engine_ || !script->file_.size())
        return;


    QJSValue evaluation = script->engine_->evaluate(function);
    if(evaluation.isError())
    {
        QString lineNumber = QString::number(evaluation.property("lineNumber").toInt());
        QString evaluationString = evaluation.toString();
        QString error("Uncaught exception at line" + lineNumber  + ":" + evaluationString );
        qDebug() << error;
        return;
    }

    evaluation.call();

}






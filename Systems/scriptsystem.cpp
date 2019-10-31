#include "scriptsystem.h"
#include <QDebug>
#include "Components/allcomponents.h"
#include "world.h"
#include "constants.h"
#include <QFile>

ScriptSystem::ScriptSystem()
{

}
ScriptSystem::~ScriptSystem()
{

}
void ScriptSystem::beginPlay()
{
    for(auto entity : mEntities)
    {
        auto scriptComp = getWorld()->getComponent<Script>(entity).value_or(nullptr);
        if(!scriptComp)
            continue;
        call(scriptComp, "beginPlay");
    }
}

void ScriptSystem::tick()
{
    for(auto entity : mEntities)
    {
        auto scriptComp = getWorld()->getComponent<Script>(entity).value_or(nullptr);
        if(!scriptComp)
            continue;
        call(scriptComp, "tick");
    }
}

void ScriptSystem::componentAdded(Script *script)
{
    if(!script)
        return;

    script->engine_->globalObject().setProperty("engine", script->engine_->newQObject(this));

}

void ScriptSystem::lolFunk(int tall)
{
    qDebug() << tall;
}

void ScriptSystem::call(Script * script, QString function)
{
    if(!script || !function.size() || !script->engine_ || !script->file_.size())
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




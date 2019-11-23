#include "scriptsystem.h"
#include <QDebug>
#include "Components/allcomponents.h"
#include "world.h"
#include "constants.h"
#include <QFile>
#include "Factories/resourcefactory.h"
#include "Managers/shadermanager.h"
#include "Script/jstimer.h"
#include "Systems/projectilesystem.h"
#include <QJsonArray>

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
    }
}

void ScriptSystem::tick(float deltaTime)
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
        for(auto& timer : timers_)
        {
            delete timer;
            timer = nullptr;
        }
    }
}

int ScriptSystem::createEntity()
{
    return getWorld()->createEntity();
}

void ScriptSystem::spawnEnemy(int owner)
{
    auto spline = getWorld()->getComponent<BSpline>(owner).value_or(nullptr);

    if(spline)
    {
        Entity entity = getWorld()->createEntity();
        getWorld()->addComponent(entity, Transform({},{},{0.2f,0.2f,0.2f}));
        getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("camera.obj"));
        getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("camera.obj"));
        getWorld()->addComponent(entity, Material(ShaderManager::instance()->colorShader(),gsl::Vector3D(1,0,0)));
        getWorld()->addComponent(entity, Npc(&spline->curve_));
    }
}

void ScriptSystem::shoot(int owner, QJsonArray npcs)
{
    auto transform = getWorld()->getComponent<Transform>(owner).value_or(nullptr);
    if(!transform) return;

    Projectile proj;

    for(const auto npc : npcs)
    {
    proj.npcPositions_.push_back(gsl::Vector3D(static_cast<float>(npc.toArray().at(0).toDouble()),0,static_cast<float>(npc.toArray().at(2).toDouble())));
    }

    Entity entity = getWorld()->createEntity();
    getWorld()->addComponent(entity, Transform(transform->position_,{},{0.1f,0.1f,0.1f}));
    getWorld()->addComponent(entity, ResourceFactory::get()->loadMesh("box2.txt"));
    getWorld()->addComponent(entity, ResourceFactory::get()->getCollision("box2.txt"));
    getWorld()->addComponent(entity, Material(ShaderManager::instance()->phongShader(),gsl::Vector3D(0,0,0)));
    getWorld()->addComponent(entity, proj);

}

QJsonValue ScriptSystem::getAllNpcLocations()
{
    QJsonArray positions;
    for(const auto& entity : getWorld()->getEntities())
    {
        auto ptr = getWorld()->getComponent<Npc>(entity).value_or(nullptr);
        if(!ptr) continue;

        auto transform = getWorld()->getComponent<Transform>(entity).value_or(nullptr);
        if(!transform) continue;
        QJsonArray pos;
        pos.insert(0,static_cast<double>(transform->position_.x));
        pos.insert(1,static_cast<double>(transform->position_.y));
        pos.insert(2,static_cast<double>(transform->position_.z));
        positions.push_back(pos);
    }
    return positions;
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
    auto scriptComp = getWorld()->getComponent<Script>(entity).value_or(nullptr);
    if(!scriptComp) return;

    script->engine_->globalObject().setProperty("engine", script->engine_->newQObject(this));
    script->engine_->globalObject().setProperty("id", entity);
    timers_.emplace_back(new JSTimer(this,entity));
    script->engine_->globalObject().setProperty("timer", script->engine_->newQObject(timers_.back()));

    load(scriptComp);
    call(scriptComp, "beginPlay");

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






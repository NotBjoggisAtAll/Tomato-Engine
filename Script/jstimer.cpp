#include "jstimer.h"
#include "world.h"
#include "Components/script.h"
#include "Systems/scriptsystem.h"

JSTimer::JSTimer(int entity, QObject* parent) : QObject(parent),owningEntity_(entity)
{

}

JSTimer::~JSTimer()
{
    delete timer_;
}

void JSTimer::setTimeout(int milliseconds)
{
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &JSTimer::timeoutDone);
    timer_->start(milliseconds);
}

void JSTimer::timeoutDone()
{
    auto scriptComp = getWorld()->getComponent<Script>(owningEntity_).value_or(nullptr);
    if(!scriptComp) return;

    static_cast<ScriptSystem*>(parent())->call(scriptComp,"timeOut");

}

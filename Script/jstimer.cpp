#include "jstimer.h"

JSTimer::JSTimer(int entity, QObject* parent) : QObject(parent),owningEntity_(entity)
{

}

JSTimer::~JSTimer()
{
    delete timer_;
}

void JSTimer::setTimeout(int milliseconds, QJSValue callback)
{
    callback_ = callback;
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &JSTimer::timeoutDone);
    timer_->start(milliseconds);
}

void JSTimer::timeoutDone()
{
    callback_.call();

}

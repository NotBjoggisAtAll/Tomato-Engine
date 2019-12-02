#include "jstimer.h"

JSTimer::JSTimer(QObject* parent) : QObject(parent) {}

JSTimer::~JSTimer()
{
    if(timer_)
    delete timer_;
}

void JSTimer::setTimeout(int milliseconds, QJSValue callback)
{
    callback_ = callback;
    if(timer_)
        delete timer_;

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &JSTimer::timeoutDone);
    timer_->start(milliseconds);
}

void JSTimer::timeoutDone()
{
    callback_.call();
}

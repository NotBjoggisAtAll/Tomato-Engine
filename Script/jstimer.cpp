#include "jstimer.h"
#include <QDebug>
JSTimer::JSTimer(QObject* parent, int entity) : QObject(parent),owningEntity_(entity)
{

}

JSTimer::~JSTimer()
{
    qDebug() << "JSTimer deleted";
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

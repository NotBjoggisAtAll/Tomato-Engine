#ifndef JSTIMER_H
#define JSTIMER_H

#include <QObject>
#include <QTimer>
#include <QJSValue>

class JSTimer : public QObject
{
    Q_OBJECT
public:
    JSTimer(int entity, QObject *parent);
    ~JSTimer();
public slots:
    void setTimeout(int milliseconds, QJSValue callback);
    void timeoutDone();
private:
    QTimer* timer_;
    QJSValue callback_;
    int owningEntity_ = -1;
};

#endif // JSTIMER_H

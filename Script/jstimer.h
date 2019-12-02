#ifndef JSTIMER_H
#define JSTIMER_H

#include <QObject>
#include <QTimer>
#include <QJSValue>

/**
 * A wrapper class around QTs QTimer.
 * Used to enable usage of the time in JavaScript.
 */
class JSTimer : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor.
     * @param parent - QObject parent.
     */
    JSTimer(QObject *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~JSTimer();
public slots:

    /**
     * Called from JavaScript.
     * Creates a timer and binds a callback function based on input.
     * @param milliseconds - int. Number of milliseconds before the callback function is called.
     * @param callback - QJSValue. The callbac function that is called when the timer is done.
     */
    void setTimeout(int milliseconds, QJSValue callback);

    /**
     * Called when the timer is done.
     * This function calls the callback function from setTimeout.
     */
    void timeoutDone();
private:
    /// The QTimer.
    QTimer* timer_ = nullptr;
    /// The callback function.
    QJSValue callback_;
};

#endif // JSTIMER_H

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <unordered_map>

class EventHandler : public QObject
{
    Q_OBJECT
public:
    EventHandler() = default;

signals:
    void leftMouseButtonPressed();
public:

    std::unordered_map<int, bool> keys_;
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    int mouseXlast_{0};
    int mouseYlast_{0};
};

#endif // EVENTHANDLER_H

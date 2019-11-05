
#include "eventhandler.h"
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "World.h"
#include "camera.h"
EventHandler::EventHandler()
{

}

bool EventHandler::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        keys_[static_cast<int>(static_cast<QMouseEvent*>(event)->button())] = true;
        emit leftMouseButtonPressed();
        return true;
    case QEvent::MouseButtonRelease:
        keys_[static_cast<int>(static_cast<QMouseEvent*>(event)->button())] = false;
        return true;
    case QEvent::KeyPress:
        keys_[static_cast<int>(static_cast<QKeyEvent*>(event)->key())] = true;
        return true;
    case QEvent::KeyRelease:
        keys_[static_cast<int>(static_cast<QKeyEvent*>(event)->key())] = false;
        return true;
    case QEvent::Wheel:
    {
        QPoint numDegrees = static_cast<QWheelEvent*>(event)->angleDelta() / 8;
        if (keys_[Qt::MouseButton::RightButton])
        {
            auto camera = getWorld()->getCurrentCamera();
            if (numDegrees.y() < 1)
                camera->setSpeed(0.001f);
            if (numDegrees.y() > 1)
                camera->setSpeed(-0.001f);
        }
        return true;
    }
    case QEvent::MouseMove:
    {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
        if (keys_[Qt::MouseButton::RightButton])
        {
            auto camera = getWorld()->getCurrentCamera();

            //Using mMouseXYlast as deltaXY so we don't need extra variables
            mouseXlast_ = mouseEvent->pos().x() - mouseXlast_;
            mouseYlast_ = mouseEvent->pos().y() - mouseYlast_;

            if (mouseXlast_ != 0)
                camera->yaw(mouseXlast_);
            if (mouseYlast_ != 0)
                camera->pitch(mouseYlast_);
        }
        mouseXlast_ = mouseEvent->pos().x();
        mouseYlast_ = mouseEvent->pos().y();
        return true;
    }
    default:
        return QObject::eventFilter(watched,event);
    }
}

#include "eventhandler.h"
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include "world.h"
#include "Components/camera.h"

bool EventHandler::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        keys_[static_cast<int>(static_cast<QMouseEvent*>(event)->button())] = true;
        if(keys_[Qt::MouseButton::LeftButton])
        {
            emit leftMouseButtonPressed();
        }
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
    case QEvent::MouseMove:
    {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
        if (keys_[Qt::MouseButton::RightButton])
        {
            auto camera = getWorld()->getComponent<Camera>(getWorld()->getCurrentCamera()).value_or(nullptr);

            //Using mMouseXYlast as deltaXY so we don't need extra variables
            mouseXlast_ = mouseEvent->pos().x() - mouseXlast_;
            mouseYlast_ = mouseEvent->pos().y() - mouseYlast_;

            if (mouseXlast_ != 0)
            {
                camera->yaw_ -= mouseXlast_ * camera->rotateSpeed_;
                camera->right_ = gsl::Vector3D(1.f, 0.f, 0.f);
                camera->right_.rotateY(camera->yaw_);
                camera->right_.normalize();
                camera->up_ = gsl::Vector3D(0.f, 1.f, 0.f);
                camera->up_.rotateX(camera->pitch_);
                camera->up_.normalize();
                camera->forward_ = camera->up_^camera->right_;

                camera->right_ = camera->forward_^camera->up_;
                camera->right_.normalize();
            }

            if (mouseYlast_ != 0)
            {
                camera->pitch_ -= mouseYlast_ * camera->rotateSpeed_;
                camera->right_ = gsl::Vector3D(1.f, 0.f, 0.f);
                camera->right_.rotateY(camera->yaw_);
                camera->right_.normalize();
                camera->up_ = gsl::Vector3D(0.f, 1.f, 0.f);
                camera->up_.rotateX(camera->pitch_);
                camera->up_.normalize();
                camera->forward_ = camera->up_^camera->right_;

                camera->right_ = camera->forward_^camera->up_;
                camera->right_.normalize();
            }

        }
        mouseXlast_ = mouseEvent->pos().x();
        mouseYlast_ = mouseEvent->pos().y();
        return true;
    }
    default:
        return QObject::eventFilter(watched,event);
    }
}

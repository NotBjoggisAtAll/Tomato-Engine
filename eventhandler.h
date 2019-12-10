#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <unordered_map>

/**
 * Usually all KeyEvents are sent to the RenderWindow class.
 * This class is an EventHandler that gets the KeyEvents instead of RenderWindow.
 * When keys are pressed they are added in a map, where the value is if it's pressed or not.
 * Some events like mousemove handled directly in this class, but most of the events are handled in other classes like InputSystem and App.
 */
class EventHandler : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor.
     */
    EventHandler() = default;

    /// Whenever a key is press its added in this map. The key is the ID of the key pressed, and the value is if its currently pressed or not.
    std::unordered_map<int, bool> keys_;

signals:
    /**
     * When the left mousebutton pressed event is called this signal is emitted.
     * The signal is recieved in App and used for mousepicking.
     */
    void leftMouseButtonPressed();

protected:
    /**
     * A eventFilter is applied to the events sent to the RenderWindow.
     * All events that are not handled in this function is sent to the RenderWindow instead.
     * All of this is handled by this line in the App constructor:
     * renderWindow_->installEventFilter(eventHandler_.get());
     * @param watched
     * @param event
     * @return
     */
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    /// The last mouse X position. Used for MouseMove event.
    int mouseXlast_ = 0;

    /// The last mouse Y position. Used for MouseMove event.
    int mouseYlast_ = 0;
};

#endif // EVENTHANDLER_H

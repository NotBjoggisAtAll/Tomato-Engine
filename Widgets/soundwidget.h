#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include <QWidget>
#include "types.h"

struct Sound;

namespace Ui {
class SoundWidget;
}
/**
 * The SoundWidget shows the Sound component in the editor.
 */
class SoundWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Default constructor.
     * Taking in an entity when created.
     * @param entity - Entity.
     */
    explicit SoundWidget(Entity entity, QWidget *parent = nullptr);

    /**
     * Default deconstructor.
     */
    ~SoundWidget();

private slots:
    /**
     * Called when the playButton is pressed.
     * Plays the sound.
     */
    void on_playButton_clicked();

    /**
     * Called when the pauseButton is pressed.
     * Pauses the sound.
     */
    void on_pauseButton_clicked();

    /**
     * Called when the stopButton is pressed.
     * Stops the sound.
     */
    void on_stopButton_clicked();

    /**
     * Called when the "..." button is pressed.
     * Used to show a menu of options.
     */
    void on_moreButton_clicked();

    /**
     * Called when clicked on Remove inside the options menu.
     * Removes the component from the entity.
     */
    void remove();

    /**
     * Called when the user has stopped editing the lineEdit fileName.
     * If the sound file is valid the component is updated with that sound and the settings from this component.
     * If not the text turns red and the sound component is emptied.
     */
    void on_fileName_editingFinished();

    /**
     * Called whenever the user edit text in the lineEdit fileName.
     * Used to turn the color back to black while writing after an invalid file.
     */
    void on_fileName_textEdited(const QString &);

    /**
     * Called whenever the user toggles the loopCheckBox.
     * Updates the sound component if the audio should loop or not.
     * @param checked - bool.
     */
    void on_loopCheckBox_toggled(bool checked);

    /**
     * Called whenever the user moves the gainSlider.
     * Updates the sound component's gain.
     * @param position - int.
     */
    void on_gainSlider_sliderMoved(int position);

private:
    /// The Sound component of the entity.
    Sound* component_ = nullptr;

    /// The entity this SoundWidget is made for.
    Entity entity_ = -1;

    Ui::SoundWidget *ui;
};

#endif // SOUNDWIDGET_H

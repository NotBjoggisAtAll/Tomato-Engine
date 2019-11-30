#ifndef GUI_H
#define GUI_H

#include "component.h"
#include "gltypes.h"
#include "GSL/vector2d.h"

/**
 * The GUI component contains information about the GUI's scale and position.
 * Use this if you want to make 2D HUD.
 */
struct GUI : public Component
{
    /**
     * Default constructor.
     */
    GUI() = default;
    /**
     * A constructor taking in a position and a scale.
     * @param position - gsl::Vector2D
     * @param scale - gsl::Vector2D
     */
    GUI(gsl::Vector2D position, gsl::Vector2D scale);
    /**
     * A constructor taking in a QJsonObject.
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject.
     */
    GUI(QJsonObject Json);
    /**
     * Makes a QJsonObject containing the component data.
     * @return Returns a QJsonObject
     */
    virtual QJsonObject toJson() override;
    /**
     * Overrides the data in the component with the data in the QJsonObject.
     * The QJsonObject needs to be in a valid Json format. Otherwise nothing is overridden.
     * @param Json - QJsonObject
     */
    virtual void fromJson(QJsonObject Json) override;

    ///The GUI's VAO. Generated with the GUIFactory.
    GLuint VAO_ = 0;
    ///The GUI's position. (0,0) is in the screen's center.
    gsl::Vector2D position_ = gsl::Vector2D(0);
    ///THe GUI's scale. Based on the screen's width and height. (1,1) covers the whole screen.
    gsl::Vector2D scale_ = gsl::Vector2D(1);

};

#endif // GUI_H

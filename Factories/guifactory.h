#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include "GSL/vector2d.h"

struct GUI;

/**
 * Responsible for making GUI components and setting up VAOs for them.
 */
class GUIFactory : public QOpenGLFunctions_4_1_Core
{
public:

    /**
     * Singleton class.
     * @return A instance of the class.
     */
    static GUIFactory* get();

    /**
     * Creates a GUI component with the given parameters. Sets up a quad for it and binds it to the VAO.
     * @param position - gsl::Vector2D. The center location of the GUI object.
     * @param scale - gsl::Vector2D. The scale based on screen size. Eg: (1,1) fill the whole screen.
     * @return A GUI object with the given paramenters.
     */
    GUI createGUI(gsl::Vector2D position = gsl::Vector2D(0), gsl::Vector2D scale = gsl::Vector2D(1));

private:
    /**
     * Default Constructor. Since this is a singleton class the constructor is private.
     */
    GUIFactory() = default;

    /**
     * Creates a quad using 2D coordinates. Binds it to VBO and a VAO.
     * @return A VAO for the given GUI.
     */
    unsigned int openGLVertexBuffers();

    /// The singleton instance pointer.
    static GUIFactory* instance_;
};

#endif // GUIFACTORY_H

#ifndef GUIFACTORY_H
#define GUIFACTORY_H

#include <QOpenGLFunctions_4_1_Core>
#include "Components/gui.h"

class GUIFactory : public QOpenGLFunctions_4_1_Core
{
public:

    static GUIFactory* get();
    GUI createGUI(gsl::Vector2D position = gsl::Vector2D(0), gsl::Vector2D scale = gsl::Vector2D(1));

private:
    GUIFactory();
    unsigned int openGLVertexBuffers();

    static GUIFactory* instance_;
};

#endif // GUIFACTORY_H

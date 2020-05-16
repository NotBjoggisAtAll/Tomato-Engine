#include <QApplication>
#include "app.h"

int main(int argc, char *argv[])
{
   // Forces the usage of desktop OpenGL
   // Attribute must be set before Q(Gui)Application is constructed:
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

  //  Makes an Qt application
    QApplication a(argc, argv);
	
    App app;

    return a.exec();

}

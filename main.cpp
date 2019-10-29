#include <QApplication>
#include "mainwindow.h"
#include "Windows/loadscene.h"

int main(int argc, char *argv[])
{
    //Forces the usage of desktop OpenGL
    //Attribute must be set before Q(Gui)Application is constructed:
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    //Makes an Qt application
    QApplication a(argc, argv);

    //Makes the Qt MainWindow and shows it.
    LoadScene l;
    l.show();
    //MainWindow w;
   // w.show();

    return a.exec();
}

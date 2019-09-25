QT          += core gui widgets

TEMPLATE    = app
CONFIG      += c++17

TARGET      = INNgine2019

PRECOMPILED_HEADER = innpch.h

INCLUDEPATH +=  ./GSL

mac {
    LIBS += -framework OpenAL
}

win32 {
    INCLUDEPATH += $(OPENAL_HOME)\\include\\AL
    LIBS *= $(OPENAL_HOME)\\libs\\Win64\\libOpenAL32.dll.a
}

HEADERS += \
    Components/allcomponents.h \
    Components/componentArray.h \
    Components/materialcomponent.h \
    Components/meshcomponent.h \
    Components/physicscomponent.h \
    Components/scriptcomponent.h \
    Components/soundcomponent.h \
    Components/transformcomponent.h \
    GSL/matrix2x2.h \
    GSL/matrix3x3.h \
    GSL/matrix4x4.h \
    GSL/vector2d.h \
    GSL/vector3d.h \
    GSL/vector4d.h \
    GSL/gsl_math.h \
    GSL/math_constants.h \
    Handlers/wavfilehandler.h \
    JBA/jbamath.h \
    JBA/matrix4x4.h \
    JBA/vector2d.h \
    JBA/vector3d.h \
    JBA/vector4d.h \
    Managers/componentManager.h \
    Managers/filemanager.h \
    Managers/shadermanager.h \
    Managers/soundmanager.h \
    Widgets/soundwidget.h \
    World.h \
    constants.h \
    entitymanager.h \
    Widgets/meshwidget.h \
    rendersystem.h \
    renderwindow.h \
    resourcefactory.h \
    shader.h \
    mainwindow.h \
    Widgets/transformwidget.h \
    soundsource.h \
    soundsystem.h \
    system.h \
    systemManager.h \
    texture.h \
    types.h \
    vertex.h \
    octahedronball.h \
    camera.h \
    octahedronball.h \
    gltypes.h \
    input.h \
    innpch.h \
    colorshader.h \
    textureshader.h \
    phongshader.h


SOURCES += main.cpp \
    GSL/matrix2x2.cpp \
    GSL/matrix3x3.cpp \
    GSL/matrix4x4.cpp \
    GSL/vector2d.cpp \
    GSL/vector3d.cpp \
    GSL/vector4d.cpp \
    GSL/gsl_math.cpp \
    Handlers/wavfilehandler.cpp \
    Managers/filemanager.cpp \
    Managers/shadermanager.cpp \
    Managers/soundmanager.cpp \
    Widgets/soundwidget.cpp \
    Widgets/meshwidget.cpp \
    World.cpp \
    rendersystem.cpp \
    resourcefactory.cpp \
    Widgets/transformwidget.cpp \
    soundsource.cpp \
    soundsystem.cpp \
    vertex.cpp \
    renderwindow.cpp \
    mainwindow.cpp \
    shader.cpp \
    texture.cpp \
    camera.cpp \
    octahedronball.cpp \
    colorshader.cpp \
    textureshader.cpp \
    phongshader.cpp

FORMS += \
    Widgets/soundwidget.ui \
    mainwindow.ui \
    Widgets/meshwidget.ui \
    Widgets/transformwidget.ui

DISTFILES += \
    Shaders/phongshader.frag \
    Shaders/phongshader.vert \
    Shaders/plainshader.frag \
    Shaders/plainshader.vert \
    Shaders/textureshader.frag \
    GSL/README.md \
    README.md \
    Shaders/textureshader.vert

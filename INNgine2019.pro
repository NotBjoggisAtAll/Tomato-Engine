QT          += core gui widgets qml

TEMPLATE    = app
CONFIG      += c++17

TARGET      = INNgine2019

mac {
    QMAKE_CXXFLAGS += --target=x86_64-apple-macosx10.14
    LIBS += -framework OpenAL
}

win32 {
    INCLUDEPATH += $(OPENAL_HOME)\\include\\AL
    LIBS *= $(OPENAL_HOME)\\libs\\Win64\\libOpenAL32.dll.a
}

HEADERS += \
    Components/allcomponents.h \
    Components/bspline.h \
    Components/camera.h \
    Components/collision.h \
    Components/component.h \
    Components/componentArray.h \
    Components/entitydata.h \
    Components/input.h \
    Components/light.h \
    Components/material.h \
    Components/mesh.h \
    Components/npc.h \
    Components/script.h \
    Components/sound.h \
    Components/transform.h \
    GSL/matrix2x2.h \
    GSL/matrix3x3.h \
    GSL/matrix4x4.h \
    GSL/vector2d.h \
    GSL/vector3d.h \
    GSL/vector4d.h \
    GSL/gsl_math.h \
    GSL/math_constants.h \
    Handlers/wavfilehandler.h \
    Managers/componentManager.h \
    Managers/filemanager.h \
    Managers/shadermanager.h \
    Managers/soundmanager.h \
    Systems/bsplinesystem.h \
    Systems/camerasystem.h \
    Systems/collisionsystem.h \
    Systems/inputsystem.h \
    Systems/movementsystem.h \
    Systems/npcsystem.h \
    Systems/scenesystem.h \
    Systems/scriptsystem.h \
    Widgets/addcomponentwidget.h \
    Widgets/bsplinewidget.h \
    Widgets/soundwidget.h \
    Windows/sceneloader.h \
    Windows/scenesaver.h \
    Windows/vector3dpicker.h \
    app.h \
    bsplinecurve.h \
    cameraclass.h \
    constants.h \
    Managers/entitymanager.h \
    Widgets/meshwidget.h \
    Systems/rendersystem.h \
    eventhandler.h \
    jsonscene.h \
    renderwindow.h \
    resourcefactory.h \
    shader.h \
    mainwindow.h \
    Widgets/transformwidget.h \
    soundsource.h \
    Systems/soundsystem.h \
    Systems/system.h \
    Managers/systemManager.h \
    texture.h \
    types.h \
    vertex.h \
    octahedronball.h \
    gltypes.h \
    colorshader.h \
    textureshader.h \
    phongshader.h \
    world.h


SOURCES += main.cpp \
    Components/bspline.cpp \
    Components/camera.cpp \
    Components/collision.cpp \
    Components/component.cpp \
    Components/entitydata.cpp \
    Components/input.cpp \
    Components/light.cpp \
    Components/material.cpp \
    Components/mesh.cpp \
    Components/npc.cpp \
    Components/sound.cpp \
    Components/transform.cpp \
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
    Systems/bsplinesystem.cpp \
    Systems/camerasystem.cpp \
    Systems/collisionsystem.cpp \
    Systems/inputsystem.cpp \
    Systems/movementsystem.cpp \
    Systems/npcsystem.cpp \
    Systems/scenesystem.cpp \
    Systems/scriptsystem.cpp \
    Systems/system.cpp \
    Widgets/addcomponentwidget.cpp \
    Widgets/bsplinewidget.cpp \
    Widgets/soundwidget.cpp \
    Widgets/meshwidget.cpp \
    Systems/rendersystem.cpp \
    Windows/sceneloader.cpp \
    Windows/scenesaver.cpp \
    Windows/vector3dpicker.cpp \
    app.cpp \
    bsplinecurve.cpp \
    cameraclass.cpp \
    eventhandler.cpp \
    jsonscene.cpp \
    resourcefactory.cpp \
    Widgets/transformwidget.cpp \
    soundsource.cpp \
    Systems/soundsystem.cpp \
    vertex.cpp \
    renderwindow.cpp \
    mainwindow.cpp \
    shader.cpp \
    texture.cpp \
    octahedronball.cpp \
    colorshader.cpp \
    textureshader.cpp \
    phongshader.cpp \
    world.cpp

FORMS += \
    Widgets/addcomponentwidget.ui \
    Widgets/bsplinewidget.ui \
    Widgets/soundwidget.ui \
    Windows/sceneloader.ui \
    Windows/scenesaver.ui \
    Windows/vector3dpicker.ui \
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

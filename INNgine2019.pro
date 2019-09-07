QT          += core gui widgets

TEMPLATE    = app
CONFIG      += c++17

TARGET      = INNgine2019

PRECOMPILED_HEADER = innpch.h

INCLUDEPATH +=  ./GSL

HEADERS += \
    Components/cameracomponent.h \
    Components/collisioncomponent.h \
    Components/component.h \
    Components/lightcomponent.h \
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
    JBA/jbamath.h \
    JBA/matrix4x4.h \
    JBA/vector2d.h \
    JBA/vector3d.h \
    JBA/vector4d.h \
    Managers/filemanager.h \
    constants.h \
    entitymanager.h \
    gameobject.h \
    rendersystem.h \
    renderwindow.h \
    resourcefactory.h \
    shader.h \
    mainwindow.h \
    triangle.h \
    texture.h \
    billboard.h \
    vertex.h \
    xyz.h \
    visualobject.h \
    octahedronball.h \
    billboard.h \
    camera.h \
    octahedronball.h \
    gltypes.h \
    trianglesurface.h \
    input.h \
    material.h \
    light.h \
    objmesh.h \
    innpch.h \
    colorshader.h \
    textureshader.h \
    skybox.h \
    phongshader.h


SOURCES += main.cpp \
    Components/component.cpp \
    GSL/matrix2x2.cpp \
    GSL/matrix3x3.cpp \
    GSL/matrix4x4.cpp \
    GSL/vector2d.cpp \
    GSL/vector3d.cpp \
    GSL/vector4d.cpp \
    GSL/gsl_math.cpp \
    Managers/filemanager.cpp \
    entitymanager.cpp \
    rendersystem.cpp \
    resourcefactory.cpp \
    vertex.cpp \
    gameobject.cpp \
    renderwindow.cpp \
    mainwindow.cpp \
    shader.cpp \
    triangle.cpp \
    texture.cpp \
    billboard.cpp \
    visualobject.cpp \
    camera.cpp \
    octahedronball.cpp \
    xyz.cpp \
    trianglesurface.cpp \
    input.cpp \
    material.cpp \
    light.cpp \
    objmesh.cpp \
    colorshader.cpp \
    textureshader.cpp \
    skybox.cpp \
    phongshader.cpp

FORMS += \
    mainwindow.ui

DISTFILES += \
    Shaders/phongshader.frag \
    Shaders/phongshader.vert \
    Shaders/plainshader.frag \
    Shaders/plainshader.vert \
    Shaders/textureshader.frag \
    GSL/README.md \
    README.md \
    Shaders/textureshader.vert

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/lib/glew/glew.c \
    src/lib/soil/image_DXT.c \
    src/lib/soil/image_helper.c \
    src/lib/soil/SOIL.c \
    src/lib/soil/stb_image_aug.c \
    src/block.cpp \
    src/entityloader.cpp \
    src/vboindexer.cpp \
    src/tangentspace.cpp \
    src/scene.cpp \
    src/renderer.cpp \
    src/settingsloader.cpp \
    src/game.cpp

HEADERS += \
    src/object3d.h \
    src/utils/logger.h \
    src/utils/loggerconsole.h \
    src/utils/loggerfile.h \
    src/utils/platform.h \
    src/utils/time.h \
    src/block.h \
    src/entityinfo.h \
    src/entityloader.h \
    src/vboindexer.h \
    src/tangentspace.h \
    src/scene.h \
    src/settings.h \
    src/game.h \
    src/renderer.h \
    src/settingsloader.h

INCLUDEPATH += $$PWD/src/include

linux:LIBS += -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi

# For MSVC2013, x86_64
win32:CONFIG += opengl
win32:LIBS += -L"$$PWD/../../../../../Program Files (x86)/Microsoft Visual Studio 12.0/VC/lib/amd64" -lglfw3dll
win32:INCLUDEPATH += "$$PWD/../../../../../Program Files (x86)/Microsoft Visual Studio 12.0/VC/include"
win32:DEPENDPATH += "$$PWD/../../../../../Program Files (x86)/Microsoft Visual Studio 12.0/VC/include"

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

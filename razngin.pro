TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += src/include/

linux:LIBS += -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi

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
    src/game.cpp \
    src/settingsloader.cpp

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


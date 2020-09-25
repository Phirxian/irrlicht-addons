TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += "-std=c++0x -D__STDC_CONSTANT_MACROS"
CXXFLAGS +="-std=c++11 -D__STDC_CONSTANT_MACROS"

SOURCES += main.cpp \
    gameintro.cpp \
    svideo.cpp \
    cguivideo.cpp


LIBS += -lIrrlicht  -lavformat -lavcodec -lavutil -lswscale -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

HEADERS += \
    gameintro.h \
    svideo.h \
    cguivideo.h

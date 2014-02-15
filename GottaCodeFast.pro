TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
QMAKE_CXXFLAGS += -std=c++0x
SOURCES += main.cpp \
    tools.cpp \
    Game.cpp \
    GottaCodeFast.cpp \
    Interface.cpp \
    Editor.cpp \
    Monster.cpp \
    Worm.cpp

HEADERS += \
    tools.hpp \
    Game.hpp \
    GottaCodeFast.hpp \
    Interface.hpp \
    Editor.hpp \
    Monster.h \
    Worm.h


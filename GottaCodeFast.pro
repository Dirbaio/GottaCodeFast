TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
QMAKE_CXXFLAGS += -std=c++0x
SOURCES += main.cpp \
    tools.cpp \
    GottaCodeFast.cpp \
    Interface.cpp \
    Editor.cpp \
    Resources.cpp \
    Monster.cpp \
    Worm.cpp \
    Spider.cpp \
    Keyboard.cpp \
    Problem.cpp \
    Player.cpp

HEADERS += \
    tools.hpp \
    GottaCodeFast.hpp \
    Interface.hpp \
    Editor.hpp \
    Resources.hpp \
    Monster.h \
    Worm.h \
    Spider.h \
    Keyboard.hpp \
    Problem.hpp \
    Player.hpp


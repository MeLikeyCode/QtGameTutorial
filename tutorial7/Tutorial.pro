#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T19:51:56
#
#-------------------------------------------------

QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tutorial
TEMPLATE = app


SOURCES += main.cpp \
    Bullet.cpp \
    Enemy.cpp \
    Game.cpp \
    Player.cpp \
    Player.cpp \
    Score.cpp \
    Health.cpp

HEADERS  += \
    Bullet.h \
    Enemy.h \
    Game.h \
    Player.h \
    Player.h \
    Score.h \
    Health.h

RESOURCES += \
    res.qrc

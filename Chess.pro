#-------------------------------------------------
#
# Project created by QtCreator 2012-10-18T23:35:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    figure.cpp

HEADERS  += mainwindow.h \
    figure.h \
    defs.h

FORMS    += mainwindow.ui

HEADERS += \
    pawn.h

SOURCES += \
    pawn.cpp

HEADERS += \
    game.h

SOURCES += \
    game.cpp

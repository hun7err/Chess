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
    figures.cpp \
    chess.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    #defs.h \
    includes.h \
    figures.h \
    chess.h \
    game.h

FORMS    += mainwindow.ui

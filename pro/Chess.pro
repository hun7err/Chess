#-------------------------------------------------
#
# Project created by QtCreator 2012-10-18T23:35:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += ../src/mainwindow.cpp \
    ../src/main.cpp \
    ../src/game.cpp \
    ../src/figures.cpp \
    ../src/chess.cpp

HEADERS  += ../include/mainwindow.h \
    ../include/includes.h \
    ../include/game.h \
    ../include/figures.h \
    ../include/chess.h

FORMS    += ../ui/mainwindow.ui

RESOURCES += ../res/resources.qrc

CONFIG(debug, debug|release) {
        TARGET = ../Chess/bin/debug/Chess
        OBJECTS_DIR = ../Chess/obj/debug
        MOC_DIR = ../Chess/moc/debug
}

CONFIG(release, debug|release) {
        TARGET = ../Chess/bin/release/Chess
        OBJECTS_DIR = ../Chess/obj/release
        MOC_DIR = ../Chess/moc/release
}

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
    ../src/chess.cpp \
    ../src/timeset.cpp \
#    ../src/about.cpp

HEADERS  += ../include/mainwindow.h \
    ../include/includes.h \
    ../include/game.h \
    ../include/figures.h \
    ../include/chess.h \
    ../include/timeset.h \
#    ../include/about.h

FORMS    += ../ui/mainwindow.ui \
            ../ui/timeset.ui \
#            ../ui/about.ui

RESOURCES += ../res/resources.qrc

CONFIG(debug, debug|release) {
        TARGET = ../bin/debug/Chess
        OBJECTS_DIR = ../obj/debug
        MOC_DIR = ../moc/debug
}

CONFIG(release, debug|release) {
        TARGET = ../bin/release/Chess
        OBJECTS_DIR = ../obj/release
        MOC_DIR = ../moc/release
}

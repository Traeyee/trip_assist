#-------------------------------------------------
#
# Project created by QtCreator 2016-05-10T16:57:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trip_assist
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    system.cpp \
    newtrip.cpp

HEADERS  += mainwindow.h \
    system.h \
    newtrip.h

FORMS    += mainwindow.ui \
    newtrip.ui

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
    system.cpp \
    newtrip.cpp \
    map.cpp \
    start.cpp

HEADERS  += \
    system.h \
    newtrip.h \
    map.h \
    start.h

FORMS    += \
    newtrip.ui \
    start.ui

RESOURCES += \
    pic.qrc

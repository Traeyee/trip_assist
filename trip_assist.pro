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
    newtrip.cpp \
    map.cpp \
    start.cpp \
    inquiry.cpp

HEADERS  += \
    newtrip.h \
    map.h \
    start.h \
    inquiry.h

FORMS    += \
    start.ui \
    newtrip.ui \
    inquiry.ui

RESOURCES += \
    pic.qrc

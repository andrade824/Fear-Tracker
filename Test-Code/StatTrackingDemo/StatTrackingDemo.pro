#-------------------------------------------------
#
# Project created by QtCreator 2014-11-21T10:13:42
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StatTrackingDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp

HEADERS  += mainwindow.h \
    graph.h

FORMS    += mainwindow.ui \
    graph.ui

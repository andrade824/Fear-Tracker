#-------------------------------------------------
#
# Project created by QtCreator 2015-01-31T15:53:50
#
#-------------------------------------------------

QT       += core gui opengl serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicsViewDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    feardata.cpp \
    feardatanode.cpp \
    trigraph.cpp \
    graphitem.cpp \
    trigraphoverlay.cpp \
    dataretrieval.cpp

HEADERS  += mainwindow.h \
    feardata.h \
    feardatanode.h \
    feartype.h \
    trigraph.h \
    graphitem.h \
    trigraphoverlay.h \
    dataretrieval.h

FORMS    += mainwindow.ui

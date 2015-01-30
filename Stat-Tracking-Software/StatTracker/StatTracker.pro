TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    feardata.cpp \
    feardatanode.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    feardata.h \
    feardatanode.h

#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T19:57:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtgui
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += ../


SOURCES += main.cpp\
        MainWindow.cpp \
    ../core/Connection.cpp \
    ../core/ConnectionFactory.cpp \
    ../core/Endpoint.cpp \
    ../core/InstancePort.cpp \
    ../core/Segment.cpp \
    graphicItems/GiSegment.cpp \
    graphicItems/convert.cpp \
    graphicItems/GiInstancePort.cpp \
    ../core/types.cpp \
    ../core/Component.cpp \
    ../core/ComponentPort.cpp \
    ../core/Instance.cpp \
    ../core/InstanceAppearance.cpp \
    graphicItems/GiInstance.cpp

HEADERS  += MainWindow.hpp \
    ../core/Connection.hpp \
    ../core/ConnectionFactory.hpp \
    ../core/Endpoint.hpp \
    ../core/InstancePort.hpp \
    ../core/Segment.hpp \
    ../core/types.hpp \
    graphicItems/GiSegment.hpp \
    graphicItems/convert.hpp \
    graphicItems/GiInstancePort.hpp \
    ../core/Component.hpp \
    ../core/ComponentPort.hpp \
    ../core/Instance.hpp \
    ../core/InstanceAppearance.hpp \
    graphicItems/GiInstance.hpp

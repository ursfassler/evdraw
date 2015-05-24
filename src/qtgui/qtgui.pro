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
    graphicItems/GiSegment.cpp \
    graphicItems/convert.cpp \
    graphicItems/GiInstancePort.cpp \
    graphicItems/GiInstance.cpp \
    ../core/component/Component.cpp \
    ../core/component/ComponentPort.cpp \
    ../core/component/InstanceAppearance.cpp \
    ../core/connection/Connection.cpp \
    ../core/connection/ConnectionFactory.cpp \
    ../core/connection/Endpoint.cpp \
    ../core/connection/Segment.cpp \
    ../core/instance/Instance.cpp \
    ../core/instance/InstancePort.cpp \
    ../core/instance/InstancePortFactory.cpp \
    ../core/util/list.cpp \
    ../core/types.cpp

HEADERS  += MainWindow.hpp \
    graphicItems/GiSegment.hpp \
    graphicItems/convert.hpp \
    graphicItems/GiInstancePort.hpp \
    graphicItems/GiInstance.hpp \
    ../core/component/Component.hpp \
    ../core/component/ComponentPort.hpp \
    ../core/component/InstanceAppearance.hpp \
    ../core/connection/Connection.hpp \
    ../core/connection/ConnectionFactory.hpp \
    ../core/connection/Endpoint.hpp \
    ../core/connection/Segment.hpp \
    ../core/instance/Instance.hpp \
    ../core/instance/InstancePort.hpp \
    ../core/instance/InstancePortFactory.hpp \
    ../core/util/list.hpp \
    ../core/util/Observed.hpp \
    ../core/types.hpp

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

LIBS += -ltinyxml

INCLUDEPATH += ../


SOURCES += main.cpp\
        MainWindow.cpp \
    graphicItems/GiSegment.cpp \
    graphicItems/convert.cpp \
    graphicItems/GiInstancePort.cpp \
    graphicItems/GiInstance.cpp \
    ../core/component/Component.cpp \
    ../core/component/ComponentFactory.cpp \
    ../core/component/ComponentPort.cpp \
    ../core/component/InstanceAppearance.cpp \
    ../core/connection/Connection.cpp \
    ../core/connection/ConnectionFactory.cpp \
    ../core/connection/Endpoint.cpp \
    ../core/connection/Segment.cpp \
    ../core/instance/Connector.cpp \
    ../core/instance/Instance.cpp \
    ../core/instance/InstanceFactory.cpp \
    ../core/instance/InstancePort.cpp \
    ../core/instance/InstancePortFactory.cpp \
    ../core/util/contract.cpp \
    ../core/Point.cpp \
    ../core/types.cpp \
    graphicItems/GiConnectionCreation.cpp \
    ../core/base/Position.cpp \
    ../core/connection/SimplePort.cpp \
    ../core/connection/DrawPort.cpp \
    ../core/implementation/Composition.cpp \
    ../file/XmlReader.cpp \
    ../core/component/Library.cpp \
    ../file/BaseParser.cpp \
    ../file/ConnectionParser.cpp \
    ../file/InstanceParser.cpp \
    ../file/Parsers.cpp \
    ../file/RizzlyPrint.cpp \
    ComponentList.cpp \
    CompositionEditor.cpp \
    CompositionToGuiUpdater.cpp

HEADERS  += MainWindow.hpp \
    graphicItems/GiSegment.hpp \
    graphicItems/convert.hpp \
    graphicItems/GiInstancePort.hpp \
    graphicItems/GiInstance.hpp \
    ../core/component/Component.hpp \
    ../core/component/ComponentFactory.hpp \
    ../core/component/ComponentPort.hpp \
    ../core/component/InstanceAppearance.hpp \
    ../core/connection/Connection.hpp \
    ../core/connection/ConnectionFactory.hpp \
    ../core/connection/Endpoint.hpp \
    ../core/connection/Segment.hpp \
    ../core/instance/Connector.hpp \
    ../core/instance/Instance.hpp \
    ../core/instance/InstanceFactory.hpp \
    ../core/instance/InstancePort.hpp \
    ../core/instance/InstancePortFactory.hpp \
    ../core/util/contract.hpp \
    ../core/util/list.hpp \
    ../core/util/Observer.hpp \
    ../core/Point.hpp \
    ../core/types.hpp \
    graphicItems/GiConnectionCreation.hpp \
    ../core/base/Position.hpp \
    ../core/connection/SimplePort.hpp \
    ../core/connection/DrawPort.hpp \
    ../core/implementation/Composition.hpp \
    ../file/XmlReader.hpp \
    ../core/component/Library.hpp \
    ../file/BaseParser.hpp \
    ../file/ConnectionParser.hpp \
    ../file/InstanceParser.hpp \
    ../file/Parsers.h \
    ../file/RizzlyPrint.hpp \
    ComponentList.hpp \
    CompositionEditor.hpp \
    CompositionToGuiUpdater.hpp

OTHER_FILES += \
    drawings/test1.evd

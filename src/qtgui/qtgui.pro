# Copyright 2015 Urs Fässler, www.bitzgi.ch
# SPDX-License-Identifier:	GPL-3.0+


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtgui
TEMPLATE = app

CONFIG += c++11

LIBS += -ltinyxml

INCLUDEPATH += ../


SOURCES += \
    CompositionToGuiUpdater.cpp \
    ../core/base/Base.cpp \
    ../core/base/Position.cpp \
    ../core/component/Component.cpp \
    ../core/component/ComponentFactory.cpp \
    ../core/component/ComponentPort.cpp \
    ../core/component/InstanceAppearance.cpp \
    ../core/component/Library.cpp \
    ../core/connection/Connection.cpp \
    ../core/connection/ConnectionFactory.cpp \
    ../core/connection/ConnectionWithPortSpecification.cpp \
    ../core/connection/DrawPort.cpp \
    ../core/connection/Endpoint.cpp \
    ../core/connection/Segment.cpp \
    ../core/implementation/Composition.cpp \
    ../core/implementation/NullImplementation.cpp \
    ../core/instance/Connector.cpp \
    ../core/instance/Instance.cpp \
    ../core/instance/InstanceFactory.cpp \
    ../core/instance/InstanceOfSpecification.cpp \
    ../core/instance/InstancePort.cpp \
    ../core/Point.cpp \
    ../core/specification/AlwaysSatisfiedSpecification.cpp \
    ../core/specification/DefaultSpecification.cpp \
    ../core/specification/OrSpecification.cpp \
    ../core/types.cpp \
    ../core/util/ChildRemover.cpp \
    ../core/util/contract.cpp \
    ../core/visitor/DefaultVisitor.cpp \
    ../core/visitor/NullConstVisitor.cpp \
    ../core/visitor/NullVisitor.cpp \
    ../file/xmlreader/BaseParser.cpp \
    ../file/xmlreader/ConnectionParser.cpp \
    ../file/xmlreader/InstanceParser.cpp \
    ../file/xmlreader/XmlReader.cpp \
    ../file/xmlwriter/XmlNodeWriter.cpp \
    ../file/xmlwriter/XmlWriter.cpp \
    CompositionDraw.cpp \
    CompositionEditor.cpp \
    graphicItems/CompositionScene.cpp \
    graphicItems/convert.cpp \
    graphicItems/GiConnectionCreation.cpp \
    graphicItems/GiInstance.cpp \
    graphicItems/GiInstancePort.cpp \
    graphicItems/GiSegment.cpp \
    main.cpp\
    MainWindow.cpp \
    Workspace.cpp \
    ../core/component/PortType.cpp \
    ../core/implementation/ImplementationType.cpp \
    view/ComboboxItemDelegate.cpp \
    ../core/instance/ConnectorFactory.cpp \
    ../core/implementation/CompositionInstance.cpp \
    ../core/implementation/CompositionFactory.cpp \
    ../core/implementation/ImplementationFactory.cpp \
    graphicItems/GiSelfInstance.cpp \
    graphicItems/MoveableLine.cpp \
    ../core/instance/InstanceObserver.cpp \
    ../qtmodel/QtConnectionItem.cpp \
    ../qtmodel/ImplementationTypeModel.cpp \
    ../qtmodel/PortTypeModel.cpp \
    view/ComponentEditor.cpp \
    ../qtmodel/ComponentItem.cpp \
    ../core/component/ComponentObserver.cpp \
    ../qtmodel/InstanceItem.cpp \
    ../core/component/ComponentPortObserver.cpp \
    ../qtmodel/PortItem.cpp \
    ../qtmodel/QtListFactory.cpp

HEADERS  += \
    CompositionToGuiUpdater.hpp \
    ../core/base/Base.hpp \
    ../core/base/Position.hpp \
    ../core/component/ComponentFactory.hpp \
    ../core/component/Component.hpp \
    ../core/component/ComponentPort.hpp \
    ../core/component/InstanceAppearance.hpp \
    ../core/component/Library.hpp \
    ../core/connection/ConnectionFactory.hpp \
    ../core/connection/Connection.hpp \
    ../core/connection/ConnectionWithPortSpecification.hpp \
    ../core/connection/DrawPort.hpp \
    ../core/connection/Endpoint.hpp \
    ../core/connection/Segment.hpp \
    ../core/implementation/Composition.hpp \
    ../core/implementation/NullImplementation.hpp \
    ../core/instance/Connector.hpp \
    ../core/instance/InstanceFactory.hpp \
    ../core/instance/Instance.hpp \
    ../core/instance/InstanceOfSpecification.hpp \
    ../core/instance/InstancePort.hpp \
    ../core/Point.hpp \
    ../core/specification/AlwaysSatisfiedSpecification.hpp \
    ../core/specification/DefaultSpecification.hpp \
    ../core/specification/OrSpecification.hpp \
    ../core/specification/Specification.hpp \
    ../core/types.hpp \
    ../core/util/ChildRemover.hpp \
    ../core/util/contract.hpp \
    ../core/util/List.hpp \
    ../core/util/Observer.hpp \
    ../core/visitor/ConstVisitor.hpp \
    ../core/visitor/DefaultVisitor.hpp \
    ../core/visitor/NullConstVisitor.hpp \
    ../core/visitor/NullVisitor.hpp \
    ../core/visitor/VisitedPrototypes.hpp \
    ../core/visitor/VisitorClient.hpp \
    ../core/visitor/Visitor.hpp \
    ../file/xmlreader/BaseParser.hpp \
    ../file/xmlreader/ConnectionParser.hpp \
    ../file/xmlreader/InstanceParser.hpp \
    ../file/xmlreader/XmlReader.hpp \
    ../file/xmlwriter/XmlNodeWriter.hpp \
    ../file/xmlwriter/XmlWriter.hpp \
    CompositionDraw.hpp \
    CompositionEditor.hpp \
    graphicItems/CompositionScene.hpp \
    graphicItems/convert.hpp \
    graphicItems/GiConnectionCreation.hpp \
    graphicItems/GiInstance.hpp \
    graphicItems/GiInstancePort.hpp \
    graphicItems/GiSegment.hpp \
    MainWindow.hpp \
    Workspace.hpp \
    ../core/component/PortType.hpp \
    ../core/implementation/ImplementationType.hpp \
    view/ComboboxItemDelegate.hpp \
    ../core/instance/ConnectorFactory.hpp \
    ../core/implementation/CompositionInstance.hpp \
    ../core/implementation/CompositionFactory.hpp \
    ../core/implementation/ImplementationFactory.hpp \
    graphicItems/GiSelfInstance.hpp \
    graphicItems/MoveableLine.hpp \
    ../core/instance/InstanceObserver.h \
    ../qtmodel/QtConnectionItem.hpp \
    ../qtmodel/ImplementationTypeModel.hpp \
    ../qtmodel/PortTypeModel.hpp \
    view/ComponentEditor.hpp \
    ../qtmodel/INameTypeItem.hpp \
    ../qtmodel/ComponentItem.hpp \
    ../qtmodel/QtNameTypeItem.hpp \
    ../qtmodel/IQtItem.hpp \
    ../qtmodel/InstanceItem.hpp \
    ../core/component/ComponentObserver.hpp \
    ../core/component/ComponentPortObserver.hpp \
    ../core/component/IComponent.hpp \
    ../core/component/IImplementation.hpp \
    ../qtmodel/PortItem.hpp \
    ../qtmodel/QtList.hpp \
    view/modelfromtype.hpp \
    ../qtmodel/QtListFactory.hpp

OTHER_FILES += \
    drawings/test1.evd

DISTFILES += \
    ../../COPYING \
    ../../README.md

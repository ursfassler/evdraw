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
    CompositionDraw.cpp \
    CompositionToGuiUpdater.cpp \
    ../core/base/Base.cpp \
    ../core/base/Position.cpp \
    ../core/component/Component.cpp \
    ../core/component/ComponentFactory.cpp \
    ../core/component/ComponentObserver.cpp \
    ../core/component/ComponentPort.cpp \
    ../core/component/ComponentPortObserver.cpp \
    ../core/component/InstanceAppearance.cpp \
    ../core/component/Library.cpp \
    ../core/component/PortType.cpp \
    ../core/connection/Connection.cpp \
    ../core/connection/ConnectionFactory.cpp \
    ../core/connection/ConnectionWithPortSpecification.cpp \
    ../core/connection/DrawPort.cpp \
    ../core/connection/Endpoint.cpp \
    ../core/connection/Segment.cpp \
    ../core/implementation/Composition.cpp \
    ../core/implementation/CompositionFactory.cpp \
    ../core/implementation/CompositionInstance.cpp \
    ../core/implementation/ImplementationFactory.cpp \
    ../core/implementation/ImplementationType.cpp \
    ../core/implementation/NullImplementation.cpp \
    ../core/instance/Connector.cpp \
    ../core/instance/ConnectorFactory.cpp \
    ../core/instance/Instance.cpp \
    ../core/instance/InstanceFactory.cpp \
    ../core/instance/InstanceObserver.cpp \
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
    graphicItems/CompositionScene.cpp \
    graphicItems/convert.cpp \
    graphicItems/GiConnectionCreation.cpp \
    graphicItems/GiInstance.cpp \
    graphicItems/GiInstancePort.cpp \
    graphicItems/GiSegment.cpp \
    graphicItems/GiSelfInstance.cpp \
    graphicItems/MoveableLine.cpp \
    main.cpp\
    MainWindow.cpp \
    ../qt/model/ComponentItem.cpp \
    ../qt/model/ImplementationTypeModel.cpp \
    ../qt/model/InstanceItem.cpp \
    ../qt/model/PortItem.cpp \
    ../qt/model/PortTypeModel.cpp \
    ../qt/model/QtConnectionItem.cpp \
    ../qt/model/QtListFactory.cpp \
    Workspace.cpp \
    ../qt/component/ComboboxItemDelegate.cpp \
    ../qt/component/ComponentEditor.cpp \
    ../qt/component/CompositionEditor.cpp

HEADERS  += \
    CompositionDraw.hpp \
    CompositionToGuiUpdater.hpp \
    ../core/base/Base.hpp \
    ../core/base/Position.hpp \
    ../core/component/ComponentFactory.hpp \
    ../core/component/Component.hpp \
    ../core/component/ComponentObserver.hpp \
    ../core/component/ComponentPort.hpp \
    ../core/component/ComponentPortObserver.hpp \
    ../core/component/IComponent.hpp \
    ../core/component/IImplementation.hpp \
    ../core/component/InstanceAppearance.hpp \
    ../core/component/Library.hpp \
    ../core/component/PortType.hpp \
    ../core/connection/ConnectionFactory.hpp \
    ../core/connection/Connection.hpp \
    ../core/connection/ConnectionWithPortSpecification.hpp \
    ../core/connection/DrawPort.hpp \
    ../core/connection/Endpoint.hpp \
    ../core/connection/Segment.hpp \
    ../core/implementation/CompositionFactory.hpp \
    ../core/implementation/Composition.hpp \
    ../core/implementation/CompositionInstance.hpp \
    ../core/implementation/ImplementationFactory.hpp \
    ../core/implementation/ImplementationType.hpp \
    ../core/implementation/NullImplementation.hpp \
    ../core/instance/ConnectorFactory.hpp \
    ../core/instance/Connector.hpp \
    ../core/instance/InstanceFactory.hpp \
    ../core/instance/Instance.hpp \
    ../core/instance/InstanceObserver.h \
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
    graphicItems/CompositionScene.hpp \
    graphicItems/convert.hpp \
    graphicItems/GiConnectionCreation.hpp \
    graphicItems/GiInstance.hpp \
    graphicItems/GiInstancePort.hpp \
    graphicItems/GiSegment.hpp \
    graphicItems/GiSelfInstance.hpp \
    graphicItems/MoveableLine.hpp \
    MainWindow.hpp \
    ../qt/model/ComponentItem.hpp \
    ../qt/model/ImplementationTypeModel.hpp \
    ../qt/model/INameTypeItem.hpp \
    ../qt/model/InstanceItem.hpp \
    ../qt/model/IQtItem.hpp \
    ../qt/model/PortItem.hpp \
    ../qt/model/PortTypeModel.hpp \
    ../qt/model/QtConnectionItem.hpp \
    ../qt/model/QtListFactory.hpp \
    ../qt/model/QtList.hpp \
    ../qt/model/QtNameTypeItem.hpp \
    Workspace.hpp \
    ../qt/component/ComboboxItemDelegate.hpp \
    ../qt/component/ComponentEditor.hpp \
    ../qt/component/CompositionEditor.hpp \
    ../qt/component/modelfromtype.hpp

OTHER_FILES += \
    drawings/test1.evd

DISTFILES += \
    ../../COPYING \
    ../../README.md

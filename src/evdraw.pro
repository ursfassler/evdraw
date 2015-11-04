# Copyright 2015 Urs Fässler, www.bitzgi.ch
# SPDX-License-Identifier:	GPL-3.0+


CONFIG -= console
CONFIG -= app_bundle
CONFIG += warn_on

QT += testlib

TARGET = testapp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror

LIBS += -ltinyxml -lcppunit

!contains(QMAKE_COMPILER, clang) {
    CONFIG(debug, debug|release) {
        LIBS += -lgcov
        QMAKE_CXXFLAGS += --coverage
    }

    coverage.target = coverage
    coverage.commands = \
        ./testapp; \
        rm moc_*.gcda; \
        lcov --directory . --base-directory $$PWD --no-external --capture --output-file coverage.info; \
        lcov --remove coverage.info "unittest/*" -o coverage.info; \
        genhtml --title "evdraw" coverage.info -o $$PWD/../coverage/
    coverage.depends = testapp
    QMAKE_EXTRA_TARGETS += coverage
}

doc.target = doc
doc.commands = doxygen $$PWD/../Doxyfile
doc.depends =
QMAKE_EXTRA_TARGETS += doc

INCLUDEPATH += .

HEADERS += \
    core/base/Base.hpp \
    core/base/Position.hpp \
    core/component/ComponentFactory.hpp \
    core/component/Component.hpp \
    core/component/ComponentObserver.hpp \
    core/component/ComponentPort.hpp \
    core/component/ComponentPortObserver.hpp \
    core/component/IComponent.hpp \
    core/component/IImplementation.hpp \
    core/component/InstanceAppearance.hpp \
    core/component/Library.hpp \
    core/component/PortType.hpp \
    core/connection/ConnectionFactory.hpp \
    core/connection/Connection.hpp \
    core/connection/ConnectionWithPortSpecification.hpp \
    core/connection/DrawPort.hpp \
    core/connection/Endpoint.hpp \
    core/connection/IPort.hpp \
    core/connection/Segment.hpp \
    core/implementation/CompositionFactory.hpp \
    core/implementation/Composition.hpp \
    core/implementation/CompositionInstance.hpp \
    core/implementation/IComposition.hpp \
    core/implementation/ICompositionInstance.hpp \
    core/implementation/ImplementationFactory.hpp \
    core/implementation/ImplementationType.hpp \
    core/implementation/NullImplementation.hpp \
    core/instance/ConnectorFactory.hpp \
    core/instance/Connector.hpp \
    core/instance/IComponentInstance.hpp \
    core/instance/IInstance.hpp \
    core/instance/InstanceFactory.hpp \
    core/instance/Instance.hpp \
    core/instance/InstanceObserver.h \
    core/instance/InstanceOfSpecification.hpp \
    core/instance/InstancePort.hpp \
    core/Point.hpp \
    core/specification/AlwaysSatisfiedSpecification.hpp \
    core/specification/DefaultSpecification.hpp \
    core/specification/OrSpecification.hpp \
    core/specification/Specification.hpp \
    core/types.hpp \
    core/util/ChildRemover.hpp \
    core/util/contract.hpp \
    core/util/error.hpp \
    core/util/List.hpp \
    core/util/Observer.hpp \
    core/util/stdlist.hpp \
    core/visitor/ConstVisitor.hpp \
    core/visitor/DefaultVisitor.hpp \
    core/visitor/NullConstVisitor.hpp \
    core/visitor/NullVisitor.hpp \
    core/visitor/VisitedPrototypes.hpp \
    core/visitor/VisitorClient.hpp \
    core/visitor/Visitor.hpp \
    file/RizzlyPrint.hpp \
    file/xmlreader/BaseParser.hpp \
    file/xmlreader/ConnectionParser.hpp \
    file/xmlreader/InstanceParser.hpp \
    file/xmlreader/XmlReader.hpp \
    file/xmlwriter/XmlNodeWriter.hpp \
    file/xmlwriter/XmlWriter.hpp \
    qt/model/ComponentItem.hpp \
    qt/model/ImplementationTypeModel.hpp \
    qt/model/INameTypeItem.hpp \
    qt/model/InstanceItem.hpp \
    qt/model/IQtItem.hpp \
    qt/model/PortItem.hpp \
    qt/model/PortTypeModel.hpp \
    qt/model/QtConnectionItem.hpp \
    qt/model/QtListFactory.hpp \
    qt/model/QtList.hpp \
    qt/model/QtNameTypeItem.hpp \
    unittest/core/base/BaseTest.hpp \
    unittest/core/base/PositionTest.hpp \
    unittest/core/component/ComponentFactoryTest.hpp \
    unittest/core/component/ComponentMock.hpp \
    unittest/core/component/ComponentObserverMock.h \
    unittest/core/component/ComponentObserverTest.hpp \
    unittest/core/component/ComponentPortObserverMock.hpp \
    unittest/core/component/ComponentPortObserverTest.hpp \
    unittest/core/component/ComponentPortTest.hpp \
    unittest/core/component/ComponentTest.hpp \
    unittest/core/component/InstanceAppearanceTest.hpp \
    unittest/core/component/LibraryTest.hpp \
    unittest/core/component/PortTypeTest.hpp \
    unittest/core/connection/ConnectionFactoryTest.hpp \
    unittest/core/connection/ConnectionTest.hpp \
    unittest/core/connection/ConnectionWithPortSpecificationTest.hpp \
    unittest/core/connection/DrawPortTest.hpp \
    unittest/core/connection/EndpointTest.hpp \
    unittest/core/connection/PortMock.hpp \
    unittest/core/connection/SegmentTest.hpp \
    unittest/core/implementation/CompositionFactoryTest.hpp \
    unittest/core/implementation/CompositionInstanceMock.hpp \
    unittest/core/implementation/CompositionInstanceTest.hpp \
    unittest/core/implementation/CompositionMock.hpp \
    unittest/core/implementation/CompositionObserverMock.h \
    unittest/core/implementation/CompositionTest.hpp \
    unittest/core/implementation/ImplementationFactoryTest.hpp \
    unittest/core/implementation/ImplementationMock.hpp \
    unittest/core/implementation/ImplementationTypeTest.hpp \
    unittest/core/implementation/NullImplementationTest.hpp \
    unittest/core/instance/ComponentInstanceMock.hpp \
    unittest/core/instance/ConnectorFactoryTest.hpp \
    unittest/core/instance/ConnectorTest.hpp \
    unittest/core/instance/InstanceFactoryTest.hpp \
    unittest/core/instance/InstanceMock.hpp \
    unittest/core/instance/InstanceObserverMock.h \
    unittest/core/instance/InstanceObserverTest.hpp \
    unittest/core/instance/InstanceOfSpecificationTest.hpp \
    unittest/core/instance/InstancePortObserverTest.hpp \
    unittest/core/instance/InstancePortTest.hpp \
    unittest/core/instance/InstanceTest.hpp \
    unittest/core/PointTest.hpp \
    unittest/core/specification/AlwaysSatisfiedSpecificationTest.hpp \
    unittest/core/specification/DefaultSpecificationTest.hpp \
    unittest/core/specification/OrSpecificationTest.hpp \
    unittest/core/specification/SpecificationTest.hpp \
    unittest/core/TypesTest.hpp \
    unittest/core/util/ChildRemoverTest.hpp \
    unittest/core/util/contractTest.hpp \
    unittest/core/util/DestructorCallCheck.h \
    unittest/core/util/errorTest.hpp \
    unittest/core/util/ListObserverMock.h \
    unittest/core/util/ListTest.h \
    unittest/core/util/ObserverTest.hpp \
    unittest/core/util/stdlistTest.hpp \
    unittest/core/visitor/ConstVisitorMock.hpp \
    unittest/core/visitor/ConstVisitorTest.hpp \
    unittest/core/visitor/DefaultVisitorMock.h \
    unittest/core/visitor/DefaultVisitorTest.hpp \
    unittest/core/visitor/NullConstVisitorTest.hpp \
    unittest/core/visitor/NullVisitorTest.hpp \
    unittest/core/visitor/VisitorClientTest.hpp \
    unittest/core/visitor/VisitorMock.h \
    unittest/core/visitor/VisitorTest.hpp \
    unittest/file/RizzlyPrintTest.hpp \
    unittest/file/xmlreader/BaseParserTest.hpp \
    unittest/file/xmlreader/ConnectionParserTest.hpp \
    unittest/file/xmlreader/InstanceParserTest.hpp \
    unittest/file/xmlreader/XmlReaderTest.hpp \
    unittest/file/xmlwriter/XmlNodeWriterTest.hpp \
    unittest/file/xmlwriter/XmlWriterTest.hpp \
    unittest/qt/qthelper.hpp \
    unittest/qt/model/ComponentItemTest.hpp \
    unittest/qt/model/ImplementationTypeModelTest.hpp \
    unittest/qt/model/InstanceItemTest.hpp \
    unittest/qt/model/NameTypeItemMock.hpp \
    unittest/qt/model/PortItemTest.hpp \
    unittest/qt/model/PortTypeModelTest.hpp \
    unittest/qt/model/QtConnectionItemTest.hpp \
    unittest/qt/model/QtItemIntMock.hpp \
    unittest/qt/model/QtListFactoryTest.hpp \
    unittest/qt/model/QtListTest.hpp \
    unittest/qt/model/QtNameTypeItemTest.hpp \
    unittest/testtypes.hpp

SOURCES += \
    core/base/Base.cpp \
    core/base/Position.cpp \
    core/component/Component.cpp \
    core/component/ComponentFactory.cpp \
    core/component/ComponentObserver.cpp \
    core/component/ComponentPort.cpp \
    core/component/ComponentPortObserver.cpp \
    core/component/InstanceAppearance.cpp \
    core/component/Library.cpp \
    core/component/PortType.cpp \
    core/connection/Connection.cpp \
    core/connection/ConnectionFactory.cpp \
    core/connection/ConnectionWithPortSpecification.cpp \
    core/connection/DrawPort.cpp \
    core/connection/Endpoint.cpp \
    core/connection/Segment.cpp \
    core/implementation/Composition.cpp \
    core/implementation/CompositionFactory.cpp \
    core/implementation/CompositionInstance.cpp \
    core/implementation/ImplementationFactory.cpp \
    core/implementation/ImplementationType.cpp \
    core/implementation/NullImplementation.cpp \
    core/instance/Connector.cpp \
    core/instance/ConnectorFactory.cpp \
    core/instance/Instance.cpp \
    core/instance/InstanceFactory.cpp \
    core/instance/InstanceObserver.cpp \
    core/instance/InstanceOfSpecification.cpp \
    core/instance/InstancePort.cpp \
    core/Point.cpp \
    core/specification/AlwaysSatisfiedSpecification.cpp \
    core/specification/DefaultSpecification.cpp \
    core/specification/OrSpecification.cpp \
    core/types.cpp \
    core/util/ChildRemover.cpp \
    core/util/contract.cpp \
    core/util/error.cpp \
    core/visitor/DefaultVisitor.cpp \
    core/visitor/NullConstVisitor.cpp \
    core/visitor/NullVisitor.cpp \
    file/RizzlyPrint.cpp \
    file/xmlreader/BaseParser.cpp \
    file/xmlreader/ConnectionParser.cpp \
    file/xmlreader/InstanceParser.cpp \
    file/xmlreader/XmlReader.cpp \
    file/xmlwriter/XmlNodeWriter.cpp \
    file/xmlwriter/XmlWriter.cpp \
    qt/model/ComponentItem.cpp \
    qt/model/ImplementationTypeModel.cpp \
    qt/model/InstanceItem.cpp \
    qt/model/PortItem.cpp \
    qt/model/PortTypeModel.cpp \
    qt/model/QtConnectionItem.cpp \
    qt/model/QtListFactory.cpp \
    unittest/core/base/BaseTest.cpp \
    unittest/core/base/PositionTest.cpp \
    unittest/core/component/ComponentFactoryTest.cpp \
    unittest/core/component/ComponentObserverTest.cpp \
    unittest/core/component/ComponentPortObserverTest.cpp \
    unittest/core/component/ComponentPortTest.cpp \
    unittest/core/component/ComponentTest.cpp \
    unittest/core/component/InstanceAppearanceTest.cpp \
    unittest/core/component/LibraryTest.cpp \
    unittest/core/component/PortTypeTest.cpp \
    unittest/core/connection/ConnectionFactoryTest.cpp \
    unittest/core/connection/ConnectionTest.cpp \
    unittest/core/connection/ConnectionWithPortSpecificationTest.cpp \
    unittest/core/connection/DrawPortTest.cpp \
    unittest/core/connection/EndpointTest.cpp \
    unittest/core/connection/PortMock.cpp \
    unittest/core/connection/SegmentTest.cpp \
    unittest/core/implementation/CompositionFactoryTest.cpp \
    unittest/core/implementation/CompositionInstanceTest.cpp \
    unittest/core/implementation/CompositionMock.cpp \
    unittest/core/implementation/CompositionObserverMock.cpp \
    unittest/core/implementation/CompositionTest.cpp \
    unittest/core/implementation/ImplementationFactoryTest.cpp \
    unittest/core/implementation/ImplementationMock.cpp \
    unittest/core/implementation/ImplementationTypeTest.cpp \
    unittest/core/implementation/NullImplementationTest.cpp \
    unittest/core/instance/ComponentInstanceMock.cpp \
    unittest/core/instance/ConnectorFactoryTest.cpp \
    unittest/core/instance/ConnectorTest.cpp \
    unittest/core/instance/InstanceFactoryTest.cpp \
    unittest/core/instance/InstanceMock.cpp \
    unittest/core/instance/InstanceObserverMock.cpp \
    unittest/core/instance/InstanceObserverTest.cpp \
    unittest/core/instance/InstanceOfSpecificationTest.cpp \
    unittest/core/instance/InstancePortObserverTest.cpp \
    unittest/core/instance/InstancePortTest.cpp \
    unittest/core/instance/InstanceTest.cpp \
    unittest/core/PointTest.cpp \
    unittest/core/specification/AlwaysSatisfiedSpecificationTest.cpp \
    unittest/core/specification/DefaultSpecificationTest.cpp \
    unittest/core/specification/OrSpecificationTest.cpp \
    unittest/core/specification/SpecificationTest.cpp \
    unittest/core/TypesTest.cpp \
    unittest/core/util/ChildRemoverTest.cpp \
    unittest/core/util/contractTest.cpp \
    unittest/core/util/errorTest.cpp \
    unittest/core/util/ListTest.cpp \
    unittest/core/util/ObserverTest.cpp \
    unittest/core/util/stdlistTest.cpp \
    unittest/core/visitor/ConstVisitorMock.cpp \
    unittest/core/visitor/ConstVisitorTest.cpp \
    unittest/core/visitor/DefaultVisitorMock.cpp \
    unittest/core/visitor/DefaultVisitorTest.cpp \
    unittest/core/visitor/NullConstVisitorTest.cpp \
    unittest/core/visitor/NullVisitorTest.cpp \
    unittest/core/visitor/VisitorClientTest.cpp \
    unittest/core/visitor/VisitorMock.cpp \
    unittest/core/visitor/VisitorTest.cpp \
    unittest/file/RizzlyPrintTest.cpp \
    unittest/file/xmlreader/BaseParserTest.cpp \
    unittest/file/xmlreader/ConnectionParserTest.cpp \
    unittest/file/xmlreader/InstanceParserTest.cpp \
    unittest/file/xmlreader/XmlReaderTest.cpp \
    unittest/file/xmlwriter/XmlNodeWriterTest.cpp \
    unittest/file/xmlwriter/XmlWriterTest.cpp \
    unittest/main.cpp \
    unittest/qt/qthelper.cpp \
    unittest/qt/model/ComponentItemTest.cpp \
    unittest/qt/model/ImplementationTypeModelTest.cpp \
    unittest/qt/model/InstanceItemTest.cpp \
    unittest/qt/model/PortItemTest.cpp \
    unittest/qt/model/PortTypeModelTest.cpp \
    unittest/qt/model/QtConnectionItemTest.cpp \
    unittest/qt/model/QtItemIntMock.cpp \
    unittest/qt/model/QtListFactoryTest.cpp \
    unittest/qt/model/QtListTest.cpp \
    unittest/qt/model/QtNameTypeItemTest.cpp \
    unittest/testtypes.cpp

DISTFILES += \
    ../README.md \
    ../COPYING \
    ../Doxyfile


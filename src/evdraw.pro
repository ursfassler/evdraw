#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T19:57:48
#
#-------------------------------------------------

CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = testapp

CONFIG += c++11

#QMAKE_CXX = clang
QMAKE_CXXFLAGS = -g -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror

LIBS += -ltinyxml -lcppunit

INCLUDEPATH += .

HEADERS += \
    core/base/Base.hpp \
    core/base/Position.hpp \
    core/component/AbstractImplementation.hpp \
    core/component/ComponentFactory.hpp \
    core/component/Component.hpp \
    core/component/ComponentPort.hpp \
    core/component/InstanceAppearance.hpp \
    core/component/Library.hpp \
    core/connection/AbstractPort.hpp \
    core/connection/ConnectionFactory.hpp \
    core/connection/Connection.hpp \
    core/connection/ConnectionWithPortSpecification.hpp \
    core/connection/DrawPort.hpp \
    core/connection/Endpoint.hpp \
    core/connection/Segment.hpp \
    core/connection/SimplePort.hpp \
    core/implementation/Composition.hpp \
    core/implementation/NullImplementation.hpp \
    core/instance/AbstractInstance.hpp \
    core/instance/Connector.hpp \
    core/instance/InstanceFactory.hpp \
    core/instance/Instance.hpp \
    core/instance/InstanceOfSpecification.hpp \
    core/instance/InstancePortFactory.hpp \
    core/instance/InstancePort.hpp \
    core/Point.hpp \
    core/specification/AlwaysSatisfiedSpecification.hpp \
    core/specification/DefaultSpecification.hpp \
    core/specification/OrSpecification.hpp \
    core/specification/Specification.hpp \
    core/types.hpp \
    core/util/ChildRemover.hpp \
    core/util/contract.hpp \
    core/util/list.hpp \
    core/util/Observer.hpp \
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
    file/xmlreader/Parsers.h \
    file/xmlreader/XmlReader.hpp \
    file/xmlwriter/XmlNodeWriter.hpp \
    file/xmlwriter/XmlWriter.hpp \
    unittest/core/base/BaseTest.hpp \
    unittest/core/base/PositionTest.hpp \
    unittest/core/component/AbstractImplementationTest.hpp \
    unittest/core/component/ComponentFactoryTest.hpp \
    unittest/core/component/ComponentObserverTest.hpp \
    unittest/core/component/ComponentPortTest.hpp \
    unittest/core/component/ComponentTest.hpp \
    unittest/core/component/InstanceAppearanceTest.hpp \
    unittest/core/component/LibraryObserverTest.hpp \
    unittest/core/component/LibraryTest.hpp \
    unittest/core/connection/ConnectionFactoryTest.hpp \
    unittest/core/connection/ConnectionTest.hpp \
    unittest/core/connection/ConnectionWithPortSpecificationTest.hpp \
    unittest/core/connection/DrawPortTest.hpp \
    unittest/core/connection/EndpointTest.hpp \
    unittest/core/connection/SegmentTest.hpp \
    unittest/core/implementation/CompositionTest.hpp \
    unittest/core/implementation/NullImplementationTest.hpp \
    unittest/core/instance/ConnectorTest.hpp \
    unittest/core/instance/InstanceFactoryTest.hpp \
    unittest/core/instance/InstanceOfSpecificationTest.hpp \
    unittest/core/instance/InstancePortTest.hpp \
    unittest/core/instance/InstanceTest.hpp \
    unittest/core/PointTest.hpp \
    unittest/core/specification/AlwaysSatisfiedSpecificationTest.hpp \
    unittest/core/specification/DefaultSpecificationTest.hpp \
    unittest/core/specification/OrSpecificationTest.hpp \
    unittest/core/specification/SpecificationTest.hpp \
    unittest/core/TypesTest.hpp \
    unittest/core/util/AlwaysSatisfiedSpecificationTest.hpp \
    unittest/core/util/ChildRemoverTest.hpp \
    unittest/core/util/contractTest.hpp \
    unittest/core/util/DefaultSpecificationTest.hpp \
    unittest/core/util/listTest.hpp \
    unittest/core/util/ObserverTest.hpp \
    unittest/core/util/OrSpecificationTest.hpp \
    unittest/core/util/SpecificationTest.hpp \
    unittest/core/visitor/ConstVisitorTest.hpp \
    unittest/core/visitor/DefaultVisitorTest.hpp \
    unittest/core/visitor/NullConstVisitorTest.hpp \
    unittest/core/visitor/NullVisitorTest.hpp \
    unittest/core/visitor/VisitorClientTest.hpp \
    unittest/core/visitor/VisitorTest.hpp \
    unittest/file/RizzlyPrintTest.hpp \
    unittest/file/xmlreader/BaseParserTest.hpp \
    unittest/file/xmlreader/ConnectionParserTest.hpp \
    unittest/file/xmlreader/InstanceParserTest.hpp \
    unittest/file/xmlreader/XmlReaderTest.hpp \
    unittest/file/xmlwriter/XmlNodeWriterTest.hpp \
    unittest/file/xmlwriter/XmlWriterTest.hpp

SOURCES += \
    core/base/Base.cpp \
    core/base/Position.cpp \
    core/component/Component.cpp \
    core/component/ComponentFactory.cpp \
    core/component/ComponentPort.cpp \
    core/component/InstanceAppearance.cpp \
    core/component/Library.cpp \
    core/connection/Connection.cpp \
    core/connection/ConnectionFactory.cpp \
    core/connection/ConnectionWithPortSpecification.cpp \
    core/connection/DrawPort.cpp \
    core/connection/Endpoint.cpp \
    core/connection/Segment.cpp \
    core/connection/SimplePort.cpp \
    core/implementation/Composition.cpp \
    core/implementation/NullImplementation.cpp \
    core/instance/Connector.cpp \
    core/instance/Instance.cpp \
    core/instance/InstanceFactory.cpp \
    core/instance/InstanceOfSpecification.cpp \
    core/instance/InstancePort.cpp \
    core/instance/InstancePortFactory.cpp \
    core/Point.cpp \
    core/specification/AlwaysSatisfiedSpecification.cpp \
    core/specification/DefaultSpecification.cpp \
    core/specification/OrSpecification.cpp \
    core/types.cpp \
    core/util/ChildRemover.cpp \
    core/util/contract.cpp \
    core/visitor/DefaultVisitor.cpp \
    core/visitor/NullConstVisitor.cpp \
    core/visitor/NullVisitor.cpp \
    file/RizzlyPrint.cpp \
    file/xmlreader/BaseParser.cpp \
    file/xmlreader/ConnectionParser.cpp \
    file/xmlreader/InstanceParser.cpp \
    file/xmlreader/Parsers.cpp \
    file/xmlreader/XmlReader.cpp \
    file/xmlwriter/XmlNodeWriter.cpp \
    file/xmlwriter/XmlWriter.cpp \
    unittest/core/base/BaseTest.cpp \
    unittest/core/base/PositionTest.cpp \
    unittest/core/component/AbstractImplementationTest.cpp \
    unittest/core/component/ComponentFactoryTest.cpp \
    unittest/core/component/ComponentObserverTest.cpp \
    unittest/core/component/ComponentPortTest.cpp \
    unittest/core/component/ComponentTest.cpp \
    unittest/core/component/InstanceAppearanceTest.cpp \
    unittest/core/component/LibraryObserverTest.cpp \
    unittest/core/component/LibraryTest.cpp \
    unittest/core/connection/ConnectionFactoryTest.cpp \
    unittest/core/connection/ConnectionTest.cpp \
    unittest/core/connection/ConnectionWithPortSpecificationTest.cpp \
    unittest/core/connection/DrawPortTest.cpp \
    unittest/core/connection/EndpointTest.cpp \
    unittest/core/connection/SegmentTest.cpp \
    unittest/core/implementation/CompositionTest.cpp \
    unittest/core/implementation/NullImplementationTest.cpp \
    unittest/core/instance/ConnectorTest.cpp \
    unittest/core/instance/InstanceFactoryTest.cpp \
    unittest/core/instance/InstanceOfSpecificationTest.cpp \
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
    unittest/core/util/listTest.cpp \
    unittest/core/util/ObserverTest.cpp \
    unittest/core/visitor/ConstVisitorTest.cpp \
    unittest/core/visitor/DefaultVisitorTest.cpp \
    unittest/core/visitor/NullConstVisitorTest.cpp \
    unittest/core/visitor/NullVisitorTest.cpp \
    unittest/core/visitor/VisitorClientTest.cpp \
    unittest/core/visitor/VisitorTest.cpp \
    unittest/file/RizzlyPrintTest.cpp \
    unittest/file/xmlreader/BaseParserTest.cpp \
    unittest/file/xmlreader/ConnectionParserTest.cpp \
    unittest/file/xmlreader/InstanceParserTest.cpp \
    unittest/file/xmlreader/XmlReaderTest.cpp \
    unittest/file/xmlwriter/XmlNodeWriterTest.cpp \
    unittest/file/xmlwriter/XmlWriterTest.cpp \
    unittest/main.cpp


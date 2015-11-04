# Copyright 2015 Urs Fässler, www.bitzgi.ch
# SPDX-License-Identifier:	GPL-3.0+


CONFIG -= console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += warn_on

QT += testlib

TARGET = testapp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Weffc++ -Werror

LIBS += -lcppunit

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

INCLUDEPATH += ../

HEADERS += \
    core/base/BaseTest.hpp \
    core/base/PositionTest.hpp \
    core/component/ComponentFactoryTest.hpp \
    core/component/ComponentMock.hpp \
    core/component/ComponentObserverMock.h \
    core/component/ComponentObserverTest.hpp \
    core/component/ComponentPortObserverMock.hpp \
    core/component/ComponentPortObserverTest.hpp \
    core/component/ComponentPortTest.hpp \
    core/component/ComponentTest.hpp \
    core/component/InstanceAppearanceTest.hpp \
    core/component/LibraryTest.hpp \
    core/component/PortTypeTest.hpp \
    core/connection/ConnectionFactoryTest.hpp \
    core/connection/ConnectionTest.hpp \
    core/connection/ConnectionWithPortSpecificationTest.hpp \
    core/connection/DrawPortTest.hpp \
    core/connection/EndpointTest.hpp \
    core/connection/PortMock.hpp \
    core/connection/SegmentTest.hpp \
    core/implementation/CompositionFactoryTest.hpp \
    core/implementation/CompositionInstanceMock.hpp \
    core/implementation/CompositionInstanceTest.hpp \
    core/implementation/CompositionMock.hpp \
    core/implementation/CompositionObserverMock.h \
    core/implementation/CompositionTest.hpp \
    core/implementation/ImplementationFactoryTest.hpp \
    core/implementation/ImplementationMock.hpp \
    core/implementation/ImplementationTypeTest.hpp \
    core/implementation/NullImplementationTest.hpp \
    core/instance/ComponentInstanceMock.hpp \
    core/instance/ConnectorFactoryTest.hpp \
    core/instance/ConnectorTest.hpp \
    core/instance/InstanceFactoryTest.hpp \
    core/instance/InstanceMock.hpp \
    core/instance/InstanceObserverMock.h \
    core/instance/InstanceObserverTest.hpp \
    core/instance/InstanceOfSpecificationTest.hpp \
    core/instance/InstancePortObserverTest.hpp \
    core/instance/InstancePortTest.hpp \
    core/instance/InstanceTest.hpp \
    core/specification/AlwaysSatisfiedSpecificationTest.hpp \
    core/specification/DefaultSpecificationTest.hpp \
    core/specification/OrSpecificationTest.hpp \
    core/specification/SpecificationTest.hpp \
    core/util/ChildRemoverTest.hpp \
    core/util/contractTest.hpp \
    core/util/DestructorCallCheck.h \
    core/util/errorTest.hpp \
    core/util/ListObserverMock.h \
    core/util/ListTest.h \
    core/util/ObserverTest.hpp \
    core/util/stdlistTest.hpp \
    core/visitor/ConstVisitorMock.hpp \
    core/visitor/ConstVisitorTest.hpp \
    core/visitor/DefaultVisitorMock.h \
    core/visitor/DefaultVisitorTest.hpp \
    core/visitor/NullConstVisitorTest.hpp \
    core/visitor/NullVisitorTest.hpp \
    core/visitor/VisitorClientTest.hpp \
    core/visitor/VisitorMock.h \
    core/visitor/VisitorTest.hpp \
    core/PointTest.hpp \
    core/TypesTest.hpp \
    testtypes.hpp \
    ../core/base/Base.hpp \
    ../core/base/Position.hpp \
    ../core/component/Component.hpp \
    ../core/component/ComponentFactory.hpp \
    ../core/component/ComponentObserver.hpp \
    ../core/component/ComponentPort.hpp \
    ../core/component/ComponentPortObserver.hpp \
    ../core/component/IComponent.hpp \
    ../core/component/IImplementation.hpp \
    ../core/component/InstanceAppearance.hpp \
    ../core/component/Library.hpp \
    ../core/component/PortType.hpp \
    ../core/connection/Connection.hpp \
    ../core/connection/ConnectionFactory.hpp \
    ../core/connection/ConnectionWithPortSpecification.hpp \
    ../core/connection/DrawPort.hpp \
    ../core/connection/Endpoint.hpp \
    ../core/connection/IPort.hpp \
    ../core/connection/Segment.hpp \
    ../core/implementation/Composition.hpp \
    ../core/implementation/CompositionFactory.hpp \
    ../core/implementation/CompositionInstance.hpp \
    ../core/implementation/IComposition.hpp \
    ../core/implementation/ICompositionInstance.hpp \
    ../core/implementation/ImplementationFactory.hpp \
    ../core/implementation/ImplementationType.hpp \
    ../core/implementation/NullImplementation.hpp \
    ../core/instance/Connector.hpp \
    ../core/instance/ConnectorFactory.hpp \
    ../core/instance/IComponentInstance.hpp \
    ../core/instance/IInstance.hpp \
    ../core/instance/Instance.hpp \
    ../core/instance/InstanceFactory.hpp \
    ../core/instance/InstanceObserver.h \
    ../core/instance/InstanceOfSpecification.hpp \
    ../core/instance/InstancePort.hpp \
    ../core/specification/AlwaysSatisfiedSpecification.hpp \
    ../core/specification/DefaultSpecification.hpp \
    ../core/specification/OrSpecification.hpp \
    ../core/specification/Specification.hpp \
    ../core/util/ChildRemover.hpp \
    ../core/util/contract.hpp \
    ../core/util/error.hpp \
    ../core/util/List.hpp \
    ../core/util/Observer.hpp \
    ../core/util/stdlist.hpp \
    ../core/visitor/ConstVisitor.hpp \
    ../core/visitor/DefaultVisitor.hpp \
    ../core/visitor/NullConstVisitor.hpp \
    ../core/visitor/NullVisitor.hpp \
    ../core/visitor/VisitedPrototypes.hpp \
    ../core/visitor/Visitor.hpp \
    ../core/visitor/VisitorClient.hpp \
    ../core/Point.hpp \
    ../core/types.hpp

SOURCES += \
    core/base/BaseTest.cpp \
    core/base/PositionTest.cpp \
    core/component/ComponentFactoryTest.cpp \
    core/component/ComponentObserverTest.cpp \
    core/component/ComponentPortObserverTest.cpp \
    core/component/ComponentPortTest.cpp \
    core/component/ComponentTest.cpp \
    core/component/InstanceAppearanceTest.cpp \
    core/component/LibraryTest.cpp \
    core/component/PortTypeTest.cpp \
    core/connection/ConnectionFactoryTest.cpp \
    core/connection/ConnectionTest.cpp \
    core/connection/ConnectionWithPortSpecificationTest.cpp \
    core/connection/DrawPortTest.cpp \
    core/connection/EndpointTest.cpp \
    core/connection/PortMock.cpp \
    core/connection/SegmentTest.cpp \
    core/implementation/CompositionFactoryTest.cpp \
    core/implementation/CompositionInstanceTest.cpp \
    core/implementation/CompositionMock.cpp \
    core/implementation/CompositionObserverMock.cpp \
    core/implementation/CompositionTest.cpp \
    core/implementation/ImplementationFactoryTest.cpp \
    core/implementation/ImplementationMock.cpp \
    core/implementation/ImplementationTypeTest.cpp \
    core/implementation/NullImplementationTest.cpp \
    core/instance/ComponentInstanceMock.cpp \
    core/instance/ConnectorFactoryTest.cpp \
    core/instance/ConnectorTest.cpp \
    core/instance/InstanceFactoryTest.cpp \
    core/instance/InstanceMock.cpp \
    core/instance/InstanceObserverMock.cpp \
    core/instance/InstanceObserverTest.cpp \
    core/instance/InstanceOfSpecificationTest.cpp \
    core/instance/InstancePortObserverTest.cpp \
    core/instance/InstancePortTest.cpp \
    core/instance/InstanceTest.cpp \
    core/specification/AlwaysSatisfiedSpecificationTest.cpp \
    core/specification/DefaultSpecificationTest.cpp \
    core/specification/OrSpecificationTest.cpp \
    core/specification/SpecificationTest.cpp \
    core/util/ChildRemoverTest.cpp \
    core/util/contractTest.cpp \
    core/util/errorTest.cpp \
    core/util/ListTest.cpp \
    core/util/ObserverTest.cpp \
    core/util/stdlistTest.cpp \
    core/visitor/ConstVisitorMock.cpp \
    core/visitor/ConstVisitorTest.cpp \
    core/visitor/DefaultVisitorMock.cpp \
    core/visitor/DefaultVisitorTest.cpp \
    core/visitor/NullConstVisitorTest.cpp \
    core/visitor/NullVisitorTest.cpp \
    core/visitor/VisitorClientTest.cpp \
    core/visitor/VisitorMock.cpp \
    core/visitor/VisitorTest.cpp \
    core/PointTest.cpp \
    core/TypesTest.cpp \
    main.cpp \
    testtypes.cpp \
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
    ../core/specification/AlwaysSatisfiedSpecification.cpp \
    ../core/specification/DefaultSpecification.cpp \
    ../core/specification/OrSpecification.cpp \
    ../core/util/ChildRemover.cpp \
    ../core/util/contract.cpp \
    ../core/util/error.cpp \
    ../core/visitor/DefaultVisitor.cpp \
    ../core/visitor/NullConstVisitor.cpp \
    ../core/visitor/NullVisitor.cpp \
    ../core/Point.cpp \
    ../core/types.cpp

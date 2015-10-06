// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "VisitorTest.hpp"
#include "../implementation/CompositionInstanceMock.hpp"
#include "../component/ComponentMock.hpp"
#include "VisitorMock.h"
#include "../connection/PortMock.hpp"

#include <core/visitor/Visitor.hpp>

#include <core/component/Component.hpp>
#include <core/component/Library.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/DrawPort.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/implementation/Composition.hpp>
#include <core/implementation/CompositionFactory.hpp>
#include <core/implementation/NullImplementation.hpp>

void VisitorTest::componentPort()
{
  VisitorMock visitor;
  ComponentPort port("thePort", PortType::Slot);

  port.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"ComponentPort:thePort"}, visitor.visited);
}

void VisitorTest::component()
{
  VisitorMock visitor;
  Component component{"component", new NullImplementation()};

  component.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"Component:component"}, visitor.visited);

  ComponentFactory::cleanup(component);
}

void VisitorTest::instance()
{
  VisitorMock visitor;
  Component *component = ComponentFactory::produce("component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  instance->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"Instance:instance"}, visitor.visited);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void VisitorTest::instancePort()
{
  VisitorMock visitor;
  Component *component = ComponentFactory::produce("component", {"port"}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));
  IPort *port = instance->getPorts().front();

  port->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"InstancePort:port"}, visitor.visited);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void VisitorTest::connection()
{
  VisitorMock visitor;
  PortMock start{"a"};
  PortMock end{"b"};
  Connection *connection = ConnectionFactory::produce(&start, &end);

  connection->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"Connection:a->b"}, visitor.visited);

  ConnectionFactory::dispose(connection);
}

void VisitorTest::composition()
{
  VisitorMock visitor;
  Composition composition{new CompositionInstanceMock()};

  composition.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"Composition"}, visitor.visited);

  CompositionFactory::cleanup(composition);
}

void VisitorTest::compositionInstance()
{
  VisitorMock visitor;
  IComponent *component = new ComponentMock();
  CompositionInstance *instance = new CompositionInstance(component);

  instance->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"CompositionInstance"}, visitor.visited);

  delete instance;
  delete component;
}

void VisitorTest::nullImplementation()
{
  VisitorMock visitor;

  NullImplementation nullImpl;
  nullImpl.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"NullImplementation"}, visitor.visited);
}

void VisitorTest::library()
{
  VisitorMock visitor;
  Library library;

  library.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"Library"}, visitor.visited);
}

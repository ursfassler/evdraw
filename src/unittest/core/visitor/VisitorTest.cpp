// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "VisitorTest.hpp"
#include "../implementation/CompositionInstanceMock.hpp"
#include "../component/ComponentMock.hpp"
#include "VisitorMock.h"

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

  ComponentPort port("", PortType::Slot);
  port.setTopIndex(10);
  port.accept(visitor);
  CPPUNIT_ASSERT_EQUAL(size_t(2*10), port.getTopIndex());
}

void VisitorTest::component()
{
  VisitorMock visitor;

  Component *component = ComponentFactory::produce("component");
  CPPUNIT_ASSERT_EQUAL(size_t(0), component->getPorts().size());
  component->accept(visitor);
  CPPUNIT_ASSERT_EQUAL(size_t(1), component->getPorts().size());

  ComponentFactory::dispose(component);
}

void VisitorTest::instance()
{
  VisitorMock visitor;

  Component *component = ComponentFactory::produce("component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  CPPUNIT_ASSERT_EQUAL(Point(0,0), instance->getOffset());
  instance->accept(visitor);
  CPPUNIT_ASSERT_EQUAL(Point(42,57), instance->getOffset());

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
  CPPUNIT_ASSERT_EQUAL(Point(100,200), port->getPosition());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void VisitorTest::connection()
{
  VisitorMock visitor;
  DrawPort start(Point(0,0));
  DrawPort end(Point(0,0));
  Connection *connection = ConnectionFactory::produce(&start, &end);

  connection->accept(visitor);
  CPPUNIT_ASSERT_EQUAL(static_cast<IPort*>(&end), connection->getStartPort());
  CPPUNIT_ASSERT_EQUAL(static_cast<IPort*>(&start), connection->getEndPort());

  ConnectionFactory::dispose(connection);
}

void VisitorTest::composition()
{
  VisitorMock visitor;

  Composition composition{new CompositionInstanceMock()};
  composition.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getInstances().size());

  CompositionFactory::cleanup(composition);
}

void VisitorTest::compositionInstance()
{
  VisitorMock visitor;

  IComponent *component = new ComponentMock();
  CompositionInstance instance{component};
  instance.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(test::sl{"CompositionInstance"}, visitor.visited);

//  delete component;
}

void VisitorTest::nullImplementation()
{
  VisitorMock visitor;

  NullImplementation nullImpl;
  nullImpl.accept(visitor);
}

void VisitorTest::library()
{
  VisitorMock visitor;

  Library library;
  library.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), library.getComponents().size());
}

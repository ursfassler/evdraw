// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConstVisitorTest.hpp"

#include "ConstVisitorMock.hpp"
#include "../implementation/CompositionInstanceMock.hpp"
#include "../component/ComponentMock.hpp"

#include <core/visitor/ConstVisitor.hpp>

#include <core/component/Component.hpp>
#include <core/component/Library.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/implementation/Composition.hpp>
#include <core/implementation/NullImplementation.hpp>
#include <core/implementation/CompositionInstance.hpp>


void ConstVisitorTest::componentPort()
{
  ConstVisitorMock visitor;

  ComponentPort port("theSlot", PortType::Slot);
  port.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("ComponentPort: theSlot"), visitor.visited[0]);
}

void ConstVisitorTest::component()
{
  ConstVisitorMock visitor;

  Component *component = ComponentFactory::produce("component");
  component->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Component: component"), visitor.visited[0]);

  ComponentFactory::dispose(component);
}

void ConstVisitorTest::componentWithPorts()
{
  ConstVisitorMock visitor;

  Component *component = ComponentFactory::produce("component", {"in1", "in2"}, {"out1"});
  component->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Component: component"), visitor.visited[0]);

  ComponentFactory::dispose(component);
}

void ConstVisitorTest::instance()
{
  ConstVisitorMock visitor;

  Component *component = ComponentFactory::produce("component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  instance->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Instance: instance"), visitor.visited[0]);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConstVisitorTest::compositionInstance()
{
  ConstVisitorMock visitor;

  ComponentMock component;
  CompositionInstance instance{&component};

  instance.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("CompositionInstance"), visitor.visited[0]);
}

void ConstVisitorTest::instancePort()
{
  ConstVisitorMock visitor;

  Component *component = ComponentFactory::produce("component", {"port"}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  AbstractPort *port = instance->getPorts().front();
  port->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("InstancePort: port"), visitor.visited[0]);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConstVisitorTest::connection()
{
  ConstVisitorMock visitor;

  Connection connection(nullptr, nullptr);
  connection.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Connection"), visitor.visited[0]);
}

void ConstVisitorTest::composition()
{
  ConstVisitorMock visitor;

  Composition composition{new CompositionInstanceMock()};
  composition.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Composition"), visitor.visited[0]);
}

void ConstVisitorTest::nullImplementation()
{
  ConstVisitorMock visitor;

  NullImplementation nullImpl;
  nullImpl.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("NullImplementation"), visitor.visited[0]);
}

void ConstVisitorTest::library()
{
  ConstVisitorMock visitor;

  Library library;
  library.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Library"), visitor.visited[0]);
}

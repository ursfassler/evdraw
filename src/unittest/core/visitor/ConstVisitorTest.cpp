// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConstVisitorTest.hpp"

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

class TestConstVisitor : public ConstVisitor
{
  public:
    TestConstVisitor() :
      visited()
    {
    }

    void visit(const ComponentPort &port)
    {
      visited.push_back("ComponentPort: " + port.getName());
    }

    void visit(const Component &component)
    {
      visited.push_back(component.getName());
    }

    void visit(const Instance &instance)
    {
      visited.push_back(instance.getName());
    }

    void visit(const InstancePort &port)
    {
      visited.push_back(port.getName());
    }

    void visit(const Connection &)
    {
      visited.push_back("connection");
    }

    void visit(const Composition &)
    {
      visited.push_back("composition");
    }

    void visit(const NullImplementation &)
    {
      visited.push_back("nullImplementation");
    }

    void visit(const Library &)
    {
      visited.push_back("library");
    }

    std::vector<std::string> visited;
};

void ConstVisitorTest::componentPort()
{
  TestConstVisitor visitor;

  ComponentPort port("theSlot", PortType::Slot);
  port.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("ComponentPort: theSlot"), visitor.visited[0]);
}

void ConstVisitorTest::component()
{
  TestConstVisitor visitor;

  Component *component = ComponentFactory::produce("component");
  component->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("component"), visitor.visited[0]);

  ComponentFactory::dispose(component);
}

void ConstVisitorTest::componentWithPorts()
{
  TestConstVisitor visitor;

  Component *component = ComponentFactory::produce("component", {"in1", "in2"}, {"out1"});
  component->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("component"), visitor.visited[0]);

  ComponentFactory::dispose(component);
}

void ConstVisitorTest::instance()
{
  TestConstVisitor visitor;

  Component *component = ComponentFactory::produce("component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  instance->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), visitor.visited[0]);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConstVisitorTest::instancePort()
{
  TestConstVisitor visitor;

  Component *component = ComponentFactory::produce("component", {"port"}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  AbstractPort *port = instance->getPorts().front();
  port->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("port"), visitor.visited[0]);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConstVisitorTest::connection()
{
  TestConstVisitor visitor;

  Connection connection(nullptr, nullptr);
  connection.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("connection"), visitor.visited[0]);
}

void ConstVisitorTest::composition()
{
  TestConstVisitor visitor;

  Composition composition;
  composition.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("composition"), visitor.visited[0]);
}

void ConstVisitorTest::nullImplementation()
{
  TestConstVisitor visitor;

  NullImplementation nullImpl;
  nullImpl.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("nullImplementation"), visitor.visited[0]);
}

void ConstVisitorTest::library()
{
  TestConstVisitor visitor;

  Library library;
  library.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("library"), visitor.visited[0]);
}

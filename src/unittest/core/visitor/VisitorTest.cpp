#include "VisitorTest.hpp"

#include <core/visitor/Visitor.hpp>

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

class TestVisitor : public Visitor
{
  public:
    TestVisitor() :
      visited()
    {
    }

    void visit(const Slot &port)
    {
      visited.push_back("Slot: " + port.getName());
    }

    void visit(const Signal &port)
    {
      visited.push_back("Signal: " + port.getName());
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

void VisitorTest::slot()
{
  TestVisitor visitor;

  Slot port("theSlot");
  port.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Slot: theSlot"), visitor.visited[0]);
}

void VisitorTest::signal()
{
  TestVisitor visitor;

  Signal port("theSignal");
  port.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("Signal: theSignal"), visitor.visited[0]);
}

void VisitorTest::component()
{
  TestVisitor visitor;

  Component *component = ComponentFactory::produce("component");
  component->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("component"), visitor.visited[0]);

  ComponentFactory::dispose(component);
}

void VisitorTest::componentWithPorts()
{
  TestVisitor visitor;

  Component *component = ComponentFactory::produce("component", {"in1", "in2"}, {"out1"});
  component->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("component"), visitor.visited[0]);

  ComponentFactory::dispose(component);
}

void VisitorTest::instance()
{
  TestVisitor visitor;

  Instance instance("instance", Point(0,0), nullptr);
  instance.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), visitor.visited[0]);
}

void VisitorTest::instancePort()
{
  TestVisitor visitor;

  Component *component = ComponentFactory::produce("component", {"port"}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  AbstractPort *port = instance->getPorts().front();
  port->accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("port"), visitor.visited[0]);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void VisitorTest::connection()
{
  TestVisitor visitor;

  Connection connection(nullptr, nullptr);
  connection.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("connection"), visitor.visited[0]);
}

void VisitorTest::composition()
{
  TestVisitor visitor;

  Composition composition;
  composition.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("composition"), visitor.visited[0]);
}

void VisitorTest::nullImplementation()
{
  TestVisitor visitor;

  NullImplementation nullImpl;
  nullImpl.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("nullImplementation"), visitor.visited[0]);
}

void VisitorTest::library()
{
  TestVisitor visitor;

  Library library;
  library.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("library"), visitor.visited[0]);
}

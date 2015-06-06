#include "VisitorTest.hpp"

#include <core/visitor/Visitor.hpp>

#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/sheet/Sheet.hpp>

class TestVisitor : public Visitor
{
  public:
    void visit(const ComponentPort &port)
    {
      visited.push_back(port.getName());
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

    void visit(const Sheet &)
    {
      visited.push_back("sheet");
    }

    std::vector<std::string> visited;
};

void VisitorTest::componentPort()
{
  TestVisitor visitor;

  ComponentPort port("port");
  port.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("port"), visitor.visited[0]);
}

void VisitorTest::component()
{
  TestVisitor visitor;

  Component component("component");
  component.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("component"), visitor.visited[0]);
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
}

void VisitorTest::connection()
{
  TestVisitor visitor;

  Connection connection(nullptr, nullptr);
  connection.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("connection"), visitor.visited[0]);
}

void VisitorTest::sheet()
{
  TestVisitor visitor;

  Sheet sheet;
  sheet.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), visitor.visited.size());
  CPPUNIT_ASSERT_EQUAL(std::string("sheet"), visitor.visited[0]);
}

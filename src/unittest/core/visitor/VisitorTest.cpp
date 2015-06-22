#include "VisitorTest.hpp"

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
#include <core/implementation/NullImplementation.hpp>

class TestVisitor : public Visitor
{
  public:
    void visit(Slot &port)
    {
      port.setTopIndex(2*port.getTopIndex());
    }

    void visit(Signal &port)
    {
      port.setTopIndex(3*port.getTopIndex());
    }

    void visit(Component &component)
    {
      component.addPortLeft(new Slot(""));
    }

    void visit(Instance &instance)
    {
      instance.addPort(new DrawPort(Point(0,0)));
    }

    void visit(InstancePort &port)
    {
      port.setOffset(Point(100,200));
    }

    void visit(Connection &connection)
    {
      AbstractPort *start = connection.getStartPort();
      AbstractPort *end = connection.getEndPort();
      connection.replaceStartPort(end);
      connection.replaceEndPort(start);
    }

    void visit(Composition &composition)
    {
      composition.addInstance(new Instance("", Point(0,0), nullptr));
    }

    void visit(NullImplementation &)
    {
    }

    void visit(Library &library)
    {
      library.add(ComponentFactory::produce(""));
    }
};

void VisitorTest::slot()
{
  TestVisitor visitor;

  Slot port("");
  port.setTopIndex(10);
  port.accept(visitor);
  CPPUNIT_ASSERT_EQUAL(size_t(2*10), port.getTopIndex());
}

void VisitorTest::signal()
{
  TestVisitor visitor;

  Signal port("");
  port.setTopIndex(10);
  port.accept(visitor);
  CPPUNIT_ASSERT_EQUAL(size_t(3*10), port.getTopIndex());
}

void VisitorTest::component()
{
  TestVisitor visitor;

  Component *component = ComponentFactory::produce("component");
  CPPUNIT_ASSERT_EQUAL(size_t(0), component->getPortLeft().size());
  component->accept(visitor);
  CPPUNIT_ASSERT_EQUAL(size_t(1), component->getPortLeft().size());

  ComponentFactory::dispose(component);
}

void VisitorTest::instance()
{
  TestVisitor visitor;

  Instance instance("instance", Point(0,0), nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(0), instance.getPorts().size());
  instance.accept(visitor);
  CPPUNIT_ASSERT_EQUAL(size_t(1), instance.getPorts().size());

  delete instance.getPorts()[0];
}

void VisitorTest::instancePort()
{
  TestVisitor visitor;

  Component *component = ComponentFactory::produce("component", {"port"}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  AbstractPort *port = instance->getPorts().front();
  port->accept(visitor);
  CPPUNIT_ASSERT_EQUAL(Point(100,200), port->getPosition());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void VisitorTest::connection()
{
  TestVisitor visitor;
  DrawPort start(Point(0,0));
  DrawPort end(Point(0,0));
  Connection *connection = ConnectionFactory::produce(&start, &end);

  connection->accept(visitor);
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractPort*>(&end), connection->getStartPort());
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractPort*>(&start), connection->getEndPort());

  ConnectionFactory::dispose(connection);
}

void VisitorTest::composition()
{
  TestVisitor visitor;

  Composition composition;
  composition.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getInstances().size());
}

void VisitorTest::nullImplementation()
{
  TestVisitor visitor;

  NullImplementation nullImpl;
  nullImpl.accept(visitor);
}

void VisitorTest::library()
{
  TestVisitor visitor;

  Library library;
  library.accept(visitor);

  CPPUNIT_ASSERT_EQUAL(size_t(1), library.getComponents().size());
}

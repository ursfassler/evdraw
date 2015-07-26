#include "DefaultVisitorTest.hpp"

#include <core/visitor/DefaultVisitor.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/ConnectionFactory.hpp>

void DefaultVisitorTest::inheritsVisitor()
{
  DefaultVisitor visitor;
  CPPUNIT_ASSERT(dynamic_cast<Visitor*>(&visitor) != nullptr);
}

void DefaultVisitorTest::setUp()
{
  library = new Library();

  componentNullImpl = ComponentFactory::produce("componentNullImpl");
  slot = new Slot("slot");
  componentNullImpl->addPort(slot);
  signal = new Signal("signal");
  componentNullImpl->addPort(signal);
  library->addComponent(componentNullImpl);

  composition = new Composition();
  instance = InstanceFactory::produce(componentNullImpl, "instance", Point(0,0));
  instanceSlot = instance->getPort("slot");
  instanceSignal = instance->getPort("signal");
  composition->addInstance(instance);
  connection = ConnectionFactory::produce(instanceSignal, instanceSlot);
  composition->addConnection(connection);
  componentComposition = new Component("componentComposition", composition);
  library->addComponent(componentComposition);
}

void DefaultVisitorTest::tearDown()
{
  delete library;
  library = nullptr;
  slot = nullptr;
  signal = nullptr;
  componentNullImpl = nullptr;
  componentComposition = nullptr;
  composition = nullptr;
  instance = nullptr;
  instanceSlot = nullptr;
  instanceSignal = nullptr;
  connection = nullptr;
}

class TestDefaultVisitor : public DefaultVisitor
{
  public:
    TestDefaultVisitor() :
      visited()
    {
    }

    void visit(Slot &port)
    {
      visited.push_back("Slot:" + port.getName());
      DefaultVisitor::visit(port);
    }

    void visit(Signal &port)
    {
      visited.push_back("Signal:" + port.getName());
      DefaultVisitor::visit(port);
    }

    void visit(InstancePort &port)
    {
      visited.push_back("InstancePort:" + port.getName());
      DefaultVisitor::visit(port);
    }

    void visit(Instance &instance)
    {
      visited.push_back("Instance:" + instance.getName());
      DefaultVisitor::visit(instance);
    }

    void visit(Connection &connection)
    {
      visited.push_back("Connection:" + connection.getStartPort()->getName() + "->" + connection.getEndPort()->getName());
      DefaultVisitor::visit(connection);
    }

    void visit(Composition &composition)
    {
      visited.push_back("Composition");
      DefaultVisitor::visit(composition);
    }

    void visit(NullImplementation &nullImplementation)
    {
      visited.push_back("NullImplementation");
      DefaultVisitor::visit(nullImplementation);
    }

    void visit(Component &component)
    {
      visited.push_back("Component:" + component.getName());
      DefaultVisitor::visit(component);
    }

    void visit(Library &library)
    {
      visited.push_back("Library");
      DefaultVisitor::visit(library);
    }

    test::sl visited;

    bool hasVisited(const std::string &value) const
    {
      for (const std::string &itr : visited)
      {
        if (itr == value)
        {
          return true;
        }
      }
      return false;
    }
};

void DefaultVisitorTest::slotVisitsOnlySlot()
{
  TestDefaultVisitor tdv;

  slot->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"Slot:slot"}), tdv.visited);
}

void DefaultVisitorTest::signalVisitsOnlySignal()
{
  TestDefaultVisitor tdv;

  signal->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"Signal:signal"}), tdv.visited);
}

void DefaultVisitorTest::instancePortVisitsOnlyInstancePort()
{
  TestDefaultVisitor tdv;

  instanceSlot->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"InstancePort:slot"}), tdv.visited);
}

void DefaultVisitorTest::instanceVisitsPorts()
{
  TestDefaultVisitor tdv;

  instance->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Instance:instance"));
  CPPUNIT_ASSERT(tdv.hasVisited("InstancePort:slot"));
  CPPUNIT_ASSERT(tdv.hasVisited("InstancePort:signal"));
}

void DefaultVisitorTest::connectionVisitsOnlyConnection()
{
  TestDefaultVisitor tdv;

  connection->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"Connection:signal->slot"}), tdv.visited);
}

void DefaultVisitorTest::compositionVisitsInstance()
{
  TestDefaultVisitor tdv;

  composition->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Composition"));
  CPPUNIT_ASSERT(tdv.hasVisited("Instance:instance"));
}

void DefaultVisitorTest::compositionVisitsConnection()
{
  TestDefaultVisitor tdv;

  composition->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Composition"));
  CPPUNIT_ASSERT(tdv.hasVisited("Connection:signal->slot"));
}

void DefaultVisitorTest::nullImplementationVisitsOnlyNullImplementation()
{
  TestDefaultVisitor tdv;

  componentNullImpl->getImplementation()->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"NullImplementation"}), tdv.visited);
}

void DefaultVisitorTest::componentVisitsPorts()
{
  TestDefaultVisitor tdv;

  componentNullImpl->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentNullImpl"));
  CPPUNIT_ASSERT(tdv.hasVisited("Signal:signal"));
  CPPUNIT_ASSERT(tdv.hasVisited("Slot:slot"));
}

void DefaultVisitorTest::componentVisitsImplementation()
{
  TestDefaultVisitor tdv;

  componentNullImpl->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentNullImpl"));
  CPPUNIT_ASSERT(tdv.hasVisited("NullImplementation"));
}

void DefaultVisitorTest::libraryVisitsComponents()
{
  TestDefaultVisitor tdv;

  library->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Library"));
  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentNullImpl"));
  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentComposition"));
}

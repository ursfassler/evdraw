#include "CompositionTest.hpp"

#include <core/implementation/Composition.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/connection/SimplePort.hpp>

void CompositionTest::create()
{
  Composition sheet;

  CPPUNIT_ASSERT_EQUAL(size_t(0), sheet.getInstances().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), sheet.getConnections().size());
}

void CompositionTest::addInstance()
{
  Composition sheet;
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  sheet.addInstance(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(1), sheet.getInstances().size());
  CPPUNIT_ASSERT_EQUAL(instance, sheet.getInstances().front());

  ComponentFactory::dispose(component);
}

void CompositionTest::addConnection()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});

  Composition sheet;
  sheet.addConnection(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(1), sheet.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, sheet.getConnections().front());
}

void CompositionTest::inheritsImplementation()
{
  Composition composition;
  CPPUNIT_ASSERT(dynamic_cast<AbstractImplementation*>(&composition) != nullptr);
}

void CompositionTest::getInstance()
{
  Composition composition;
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition.addInstance(instance);
  CPPUNIT_ASSERT_EQUAL(instance, composition.getInstance("instance"));

  ComponentFactory::dispose(component);
}

void CompositionTest::removeConnection()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});

  Composition sheet;
  sheet.addConnection(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(1), sheet.getConnections().size());
  sheet.removeConnection(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(0), sheet.getConnections().size());

  ConnectionFactory::dispose(connection);
}

class SheetObserverTest : public CompositionObserver
{
  public:
    virtual void instanceAdded(Instance *instance)
    {
      lastInstanceAdded = instance;
    }

    virtual void connectionAdded(Connection *connection)
    {
      lastConnectionAdded = connection;
    }

    virtual void finishConnectionUnderConstruction(Connection *connection)
    {
      lastFinishConnectionUnderConstruction = connection;
    }

    virtual void addConnectionUnderConstruction(Connection *connection)
    {
      lastAddConnectionUnderConstruction = connection;
    }

    Instance *lastInstanceAdded = nullptr;
    Connection *lastConnectionAdded = nullptr;
    Connection *lastFinishConnectionUnderConstruction = nullptr;
    Connection *lastAddConnectionUnderConstruction = nullptr;
};

void CompositionTest::notifyWhenAddInstance()
{
  Composition sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);

  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  sheet.addInstance(instance);

  CPPUNIT_ASSERT_EQUAL(instance, observer.lastInstanceAdded);

  sheet.unregisterObserver(&observer);
}

void CompositionTest::notifyWhenAddConnection()
{
  Composition sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);

  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});
  sheet.addConnection(connection);

  CPPUNIT_ASSERT_EQUAL(connection, observer.lastConnectionAdded);

  sheet.unregisterObserver(&observer);
}

void CompositionTest::addConnectionUnderConstructionNotifiesObserver()
{
  Composition sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);
  Instance instance("", Point(0,0), nullptr);
  InstancePort startPort(&instance, nullptr, Point(0,0));
  InstancePort endPort(&instance, nullptr, Point(0,0));

  sheet.startConnectionConstruction(&startPort, &endPort);
  CPPUNIT_ASSERT_EQUAL(sheet.getConnectionUnderConstruction(), observer.lastAddConnectionUnderConstruction);

  sheet.unregisterObserver(&observer);
}

void CompositionTest::canNotOverwriteConnectionUnderConstructio()
{
  Composition sheet;
  Instance instance("", Point(0,0), nullptr);
  InstancePort startPort(&instance, nullptr, Point(0,0));
  InstancePort endPort(&instance, nullptr, Point(0,0));
  sheet.startConnectionConstruction(&startPort, &endPort);

  CPPUNIT_ASSERT_THROW(sheet.startConnectionConstruction(&startPort, &endPort), PreconditionError);
}

void CompositionTest::finishConnectionCreation()
{
  Instance instance("", Point(0,0), nullptr);
  InstancePort startPort(&instance, nullptr, Point(0,0));
  SimplePort tmpEnd;
  InstancePort endPort(&instance, nullptr, Point(0,0));
  Composition sheet;
  sheet.startConnectionConstruction(&startPort, &tmpEnd);
  Connection *connection = sheet.getConnectionUnderConstruction();

  sheet.finishConnectionConstruction(&endPort);

  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractPort*>(&endPort), connection->getEndPort());
  CPPUNIT_ASSERT_EQUAL(size_t(1), sheet.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, sheet.getConnections().front());
  CPPUNIT_ASSERT(!sheet.hasConnectionUnderConstruction());
}
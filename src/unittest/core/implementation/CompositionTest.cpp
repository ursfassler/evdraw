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
  Composition *composition = new Composition();
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getInstances().size());
  CPPUNIT_ASSERT_EQUAL(instance, composition->getInstances().front());

  delete composition;
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
  Composition *composition = new Composition();
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);
  CPPUNIT_ASSERT_EQUAL(instance, composition->getInstance("instance"));

  delete composition;
  ComponentFactory::dispose(component);
}

void CompositionTest::removeInstance()
{
  Composition *composition = new Composition();
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);
  composition->removeInstance(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getInstances().size());

  delete composition;
  InstanceFactory::dispose(instance);
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

void CompositionTest::removeInstanceRemovesDependantConnections()
{
  Composition composition;

  Component *component = ComponentFactory::produce("Component", {"in"}, {"out"});
  Instance *instance = InstanceFactory::produce(component, "Instance", Point(0,0));
  composition.addInstance(instance);

  Connection *connection = ConnectionFactory::produce(instance->getPort("out"), instance->getPort("out"));
  composition.addConnection(connection);

  composition.removeInstance(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

class SheetObserverTest : public CompositionObserver
{
  public:
    virtual void instanceAdded(Instance *instance)
    {
      lastInstanceAdded = instance;
    }

    virtual void instanceRemoved(Instance *instance)
    {
      lastInstanceRemoved = instance;
    }

    virtual void connectionAdded(Connection *connection)
    {
      lastConnectionAdded = connection;
    }

    virtual void connectionRemoved(Connection *connection)
    {
      lastConnectionRemoved = connection;
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
    Instance *lastInstanceRemoved = nullptr;
    Connection *lastConnectionAdded = nullptr;
    Connection *lastConnectionRemoved = nullptr;
    Connection *lastFinishConnectionUnderConstruction = nullptr;
    Connection *lastAddConnectionUnderConstruction = nullptr;
};

void CompositionTest::notifyWhenAddInstance()
{
  Composition *composition = new Composition();
  SheetObserverTest observer;
  composition->registerObserver(&observer);

  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);

  CPPUNIT_ASSERT_EQUAL(instance, observer.lastInstanceAdded);

  composition->unregisterObserver(&observer);
  delete composition;
  ComponentFactory::dispose(component);
}

void CompositionTest::notifyWhenAddConnection()
{
  Composition *composition = new Composition();
  SheetObserverTest observer;
  composition->registerObserver(&observer);

  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});
  composition->addConnection(connection);

  CPPUNIT_ASSERT_EQUAL(connection, observer.lastConnectionAdded);

  composition->unregisterObserver(&observer);
  delete composition;
}

void CompositionTest::notifyWhenRemoveInstance()
{
  Composition *composition = new Composition();
  SheetObserverTest observer;
  composition->registerObserver(&observer);
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);
  composition->removeInstance(instance);

  CPPUNIT_ASSERT_EQUAL(instance, observer.lastInstanceRemoved);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
  delete composition;
}

void CompositionTest::notifyWhenRemoveConnection()
{
  Composition *composition = new Composition();
  SheetObserverTest observer;
  composition->registerObserver(&observer);

  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});
  composition->addConnection(connection);
  composition->removeConnection(connection);

  CPPUNIT_ASSERT_EQUAL(connection, observer.lastConnectionRemoved);

  composition->unregisterObserver(&observer);
  ConnectionFactory::dispose(connection);
  delete composition;
}

void CompositionTest::addConnectionUnderConstructionNotifiesObserver()
{
  SimplePort startPort;
  SimplePort endPort;

  SheetObserverTest observer;
  Composition composition;
  composition.registerObserver(&observer);

  composition.startConnectionConstruction(&startPort, &endPort);
  CPPUNIT_ASSERT_EQUAL(composition.getConnectionUnderConstruction(), observer.lastAddConnectionUnderConstruction);

  composition.unregisterObserver(&observer);
}

void CompositionTest::canNotOverwriteConnectionUnderConstructio()
{
  SimplePort startPort;
  SimplePort endPort;

  Composition composition;
  composition.startConnectionConstruction(&startPort, &endPort);

  CPPUNIT_ASSERT_THROW(composition.startConnectionConstruction(&startPort, &endPort), PreconditionError);
}

void CompositionTest::finishConnectionCreation()
{
  SimplePort startPort;
  SimplePort tmpEnd;
  SimplePort endPort;

  Composition composition;
  composition.startConnectionConstruction(&startPort, &tmpEnd);
  Connection *connection = composition.getConnectionUnderConstruction();

  composition.finishConnectionConstruction(&endPort);

  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractPort*>(&endPort), connection->getEndPort());
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, composition.getConnections().front());
  CPPUNIT_ASSERT(!composition.hasConnectionUnderConstruction());
}

void CompositionTest::deleteInstancePortRemovesDependantConnections()
{
  Component *comp1 = ComponentFactory::produce("comp1", {"in"}, {"out"});
  Composition *composition = new Composition();
  Instance *inst = InstanceFactory::produce(comp1, "inst", Point(0,0));
  composition->addInstance(inst);
  AbstractPort *portOut = inst->getPort("out");
  AbstractPort *portIn = inst->getPort("in");
  Connection *connection = ConnectionFactory::produce(portOut, portIn);
  composition->addConnection(connection);

  ComponentPort *port = comp1->getPorts()[0];
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getConnections().size());
  comp1->deletePort(port);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getConnections().size());

  delete composition;
  ComponentFactory::dispose(comp1);
}

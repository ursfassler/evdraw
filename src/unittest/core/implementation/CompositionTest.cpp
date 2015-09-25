// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionTest.hpp"
#include "CompositionInstanceMock.hpp"

#include <core/implementation/Composition.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/connection/SimplePort.hpp>

void CompositionTest::create()
{
  ICompositionInstance *instance = new CompositionInstanceMock();
  Composition composition(instance);

  CPPUNIT_ASSERT_EQUAL(instance, composition.getSelfInstance());
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getInstances().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());
}

void CompositionTest::addInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
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

  Composition composition{new CompositionInstanceMock()};
  composition.addConnection(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, composition.getConnections().front());
}

void CompositionTest::inherits_implementation()
{
  Composition composition{new CompositionInstanceMock()};
  CPPUNIT_ASSERT(dynamic_cast<AbstractImplementation*>(&composition) != nullptr);
}

void CompositionTest::getInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);
  CPPUNIT_ASSERT_EQUAL(instance, composition->getInstance("instance"));

  delete composition;
  ComponentFactory::dispose(component);
}

void CompositionTest::deleteInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);
  composition->deleteInstance(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getInstances().size());

  delete composition;
  ComponentFactory::dispose(component);
}

void CompositionTest::deleteConnection()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});

  Composition composition{new CompositionInstanceMock()};
  composition.addConnection(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getConnections().size());
  composition.deleteConnection(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());
}

void CompositionTest::deleteInstance_removes_dependant_connections()
{
  Composition composition{new CompositionInstanceMock()};

  Component *component = ComponentFactory::produce("Component", {"in"}, {"out"});
  Instance *instance = InstanceFactory::produce(component, "Instance", Point(0,0));
  composition.addInstance(instance);

  Connection *connection = ConnectionFactory::produce(instance->getPort("out"), instance->getPort("out"));
  composition.addConnection(connection);

  composition.deleteInstance(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());

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

void CompositionTest::notify_when_addInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
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

void CompositionTest::notify_when_addConnection()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
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

void CompositionTest::notify_when_deleteInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  SheetObserverTest observer;
  composition->registerObserver(&observer);
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->addInstance(instance);
  composition->deleteInstance(instance);

  CPPUNIT_ASSERT_EQUAL(instance, observer.lastInstanceRemoved);

  ComponentFactory::dispose(component);
  composition->unregisterObserver(&observer);
  delete composition;
}

void CompositionTest::notify_when_deleteConnection()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  SheetObserverTest observer;
  composition->registerObserver(&observer);

  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});
  composition->addConnection(connection);
  composition->deleteConnection(connection);

  CPPUNIT_ASSERT_EQUAL(connection, observer.lastConnectionRemoved);

  composition->unregisterObserver(&observer);
  delete composition;
}

void CompositionTest::addConnectionUnderConstruction_notifies_observer()
{
  SimplePort startPort;
  SimplePort endPort;

  SheetObserverTest observer;
  Composition composition{new CompositionInstanceMock()};
  composition.registerObserver(&observer);

  composition.startConnectionConstruction(&startPort, &endPort);
  CPPUNIT_ASSERT_EQUAL(composition.getConnectionUnderConstruction(), observer.lastAddConnectionUnderConstruction);

  composition.unregisterObserver(&observer);
}

void CompositionTest::can_not_overwrite_connectionUnderConstruction()
{
  SimplePort startPort;
  SimplePort endPort;

  Composition composition{new CompositionInstanceMock()};
  composition.startConnectionConstruction(&startPort, &endPort);

  CPPUNIT_ASSERT_THROW(composition.startConnectionConstruction(&startPort, &endPort), PreconditionError);
}

void CompositionTest::finishConnectionCreation()
{
  SimplePort startPort;
  SimplePort tmpEnd;
  SimplePort endPort;

  Composition composition{new CompositionInstanceMock()};
  composition.startConnectionConstruction(&startPort, &tmpEnd);
  Connection *connection = composition.getConnectionUnderConstruction();

  composition.finishConnectionConstruction(&endPort);

  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractPort*>(&endPort), connection->getEndPort());
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, composition.getConnections().front());
  CPPUNIT_ASSERT(!composition.hasConnectionUnderConstruction());
}

void CompositionTest::has_instance_with_his_parent_component()
{
  ICompositionInstance *compInstance = new CompositionInstanceMock();
  Composition *composition = new Composition(compInstance);

  CPPUNIT_ASSERT_EQUAL(compInstance, composition->getSelfInstance());

  delete composition;
}

void CompositionTest::deleteInstancePort_removes_dependant_connections()
{
  Component *comp1 = ComponentFactory::produce("comp1", {"in"}, {"out"});
  Composition *composition = new Composition(new CompositionInstanceMock());
  Instance *inst = InstanceFactory::produce(comp1, "inst", Point(0,0));
  composition->addInstance(inst);
  InstancePort *portOut = inst->getPort("out");
  InstancePort *portIn = inst->getPort("in");
  Connection *connection = ConnectionFactory::produce(portOut, portIn);
  composition->addConnection(connection);

  ComponentPort *port = comp1->getPorts()[0];
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getConnections().size());
  comp1->deletePort(port);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getConnections().size());

  delete composition;
  ComponentFactory::dispose(comp1);
}

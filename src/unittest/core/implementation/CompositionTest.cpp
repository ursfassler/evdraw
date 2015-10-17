// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionTest.hpp"
#include "CompositionInstanceMock.hpp"
#include "../connection/PortMock.hpp"
#include "CompositionObserverMock.h"

#include <core/implementation/Composition.hpp>
#include <core/implementation/CompositionFactory.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/ConnectionFactory.hpp>

void CompositionTest::create()
{
  ICompositionInstance *instance = new CompositionInstanceMock();
  Composition composition(instance);

  CPPUNIT_ASSERT_EQUAL(instance, composition.getSelfInstance());
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getInstances().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());

  CompositionFactory::cleanup(composition);
}

void CompositionTest::addInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->getInstances().add(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getInstances().size());
  CPPUNIT_ASSERT_EQUAL(instance, composition->getInstances().front());


  CompositionFactory::dispose(composition);
  ComponentFactory::dispose(component);
}

void CompositionTest::addConnection()
{
  PortMock startPort;
  PortMock endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});

  Composition composition{new CompositionInstanceMock()};
  composition.getConnections().add(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, composition.getConnections().front());

  CompositionFactory::cleanup(composition);
}

void CompositionTest::inherits_implementation()
{
  Composition composition{new CompositionInstanceMock()};
  CPPUNIT_ASSERT(dynamic_cast<IImplementation*>(&composition) != nullptr);

  CompositionFactory::cleanup(composition);
}

void CompositionTest::getInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->getInstances().add(instance);
  CPPUNIT_ASSERT_EQUAL(instance, composition->getInstance("instance"));

  CompositionFactory::dispose(composition);
  ComponentFactory::dispose(component);
}

void CompositionTest::deleteInstance()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  composition->getInstances().add(instance);
  composition->getInstances().remove(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getInstances().size());

  CompositionFactory::dispose(composition);
  ComponentFactory::dispose(component);
}

void CompositionTest::deleteConnection()
{
  PortMock startPort;
  PortMock endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});

  Composition composition{new CompositionInstanceMock()};
  composition.getConnections().add(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getConnections().size());
  composition.getConnections().remove(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());

  CompositionFactory::cleanup(composition);
}

void CompositionTest::deleteInstance_removes_dependant_connections()
{
  Composition composition{new CompositionInstanceMock()};

  Component *component = ComponentFactory::produce("Component", {"in"}, {"out"});
  Instance *instance = InstanceFactory::produce(component, "Instance", Point(0,0));
  composition.getInstances().add(instance);

  Connection *connection = ConnectionFactory::produce(instance->getPort("out"), instance->getPort("out"));
  composition.getConnections().add(connection);

  composition.getInstances().remove(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition.getConnections().size());

  ComponentFactory::dispose(component);
  CompositionFactory::cleanup(composition);
}

void CompositionTest::addConnectionUnderConstruction_notifies_observer()
{
  PortMock startPort;
  PortMock endPort;

  CompositionObserverMock observer;
  Composition composition{new CompositionInstanceMock()};
  composition.registerObserver(&observer);

  composition.startConnectionConstruction(&startPort, &endPort);
  CPPUNIT_ASSERT_EQUAL(composition.getConnectionUnderConstruction(), observer.lastAddConnectionUnderConstruction);

  composition.unregisterObserver(&observer);
  CompositionFactory::cleanup(composition);
}

void CompositionTest::can_not_overwrite_connectionUnderConstruction()
{
  PortMock startPort;
  PortMock endPort;

  Composition composition{new CompositionInstanceMock()};
  composition.startConnectionConstruction(&startPort, &endPort);

  CPPUNIT_ASSERT_THROW(composition.startConnectionConstruction(&startPort, &endPort), PreconditionError);
  CompositionFactory::cleanup(composition);
}

void CompositionTest::finishConnectionCreation()
{
  PortMock startPort;
  PortMock tmpEnd;
  PortMock endPort;

  Composition composition{new CompositionInstanceMock()};
  composition.startConnectionConstruction(&startPort, &tmpEnd);
  Connection *connection = composition.getConnectionUnderConstruction();

  composition.finishConnectionConstruction(&endPort);

  CPPUNIT_ASSERT_EQUAL(dynamic_cast<IPort*>(&endPort), connection->getEndPort());
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, composition.getConnections().front());
  CPPUNIT_ASSERT(!composition.hasConnectionUnderConstruction());

  CompositionFactory::cleanup(composition);
}

void CompositionTest::has_instance_with_his_parent_component()
{
  ICompositionInstance *compInstance = new CompositionInstanceMock();
  Composition *composition = new Composition(compInstance);

  CPPUNIT_ASSERT_EQUAL(compInstance, composition->getSelfInstance());

  CompositionFactory::dispose(composition);
}

void CompositionTest::deleteInstancePort_removes_dependant_connections()
{
  Component *comp1 = ComponentFactory::produce("comp1", {"in"}, {"out"});
  Composition *composition = new Composition(new CompositionInstanceMock());
  Instance *inst = InstanceFactory::produce(comp1, "inst", Point(0,0));
  composition->getInstances().add(inst);
  InstancePort *portOut = inst->getPort("out");
  InstancePort *portIn = inst->getPort("in");
  Connection *connection = ConnectionFactory::produce(portOut, portIn);
  composition->getConnections().add(connection);

  ComponentPort *port = comp1->getPorts()[0];
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getConnections().size());
  comp1->getPorts().remove(port);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getConnections().size());

  CompositionFactory::dispose(composition);
  ComponentFactory::dispose(comp1);
}

void CompositionTest::delete_selfInstance_port_removes_dependant_connections()
{
  Component *comp1 = ComponentFactory::produce("comp1", {"in"}, {"out"});
  Composition *composition = new Composition(new CompositionInstance(comp1));
  comp1->setImplementation(composition);

  const auto inst = composition->getSelfInstance();
  auto portIn = inst->getPorts()[0];
  auto portOut = inst->getPorts()[1];
  auto connection = ConnectionFactory::produce(portIn, portOut);
  composition->getConnections().add(connection);

  ComponentPort *port = comp1->getPorts()[0];
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getConnections().size());
  comp1->getPorts().remove(port);
  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getConnections().size());

  ComponentFactory::dispose(comp1);
}

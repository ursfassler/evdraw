// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "DefaultVisitorTest.hpp"

#include "DefaultVisitorMock.h"
#include "../component/ComponentMock.hpp"

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
  slot = new ComponentPort("slot", PortType::Slot);
  componentNullImpl->addPort(slot);
  signal = new ComponentPort("signal", PortType::Signal);
  componentNullImpl->addPort(signal);
  library->addComponent(componentNullImpl);

  compositionInstance = new CompositionInstanceMock();
  composition = new Composition(compositionInstance);
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
  compositionInstance = nullptr;
  instance = nullptr;
  instanceSlot = nullptr;
  instanceSignal = nullptr;
  connection = nullptr;
}

void DefaultVisitorTest::componentPortVisitsOnlyComponentPort()
{
  DefaultVisitorMock tdv;

  slot->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"ComponentPort:slot"}), tdv.visited);
}

void DefaultVisitorTest::instancePortVisitsOnlyInstancePort()
{
  DefaultVisitorMock tdv;

  instanceSlot->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"InstancePort:slot"}), tdv.visited);
}

void DefaultVisitorTest::instanceVisitsPorts()
{
  DefaultVisitorMock tdv;

  instance->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Instance:instance"));
  CPPUNIT_ASSERT(tdv.hasVisited("InstancePort:slot"));
  CPPUNIT_ASSERT(tdv.hasVisited("InstancePort:signal"));
}

void DefaultVisitorTest::connectionVisitsOnlyConnection()
{
  DefaultVisitorMock tdv;

  connection->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"Connection:signal->slot"}), tdv.visited);
}

void DefaultVisitorTest::compositionVisitsSelfInstance()
{
  DefaultVisitorMock tdv;

  composition->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Composition"));
  CPPUNIT_ASSERT_EQUAL(size_t(1), compositionInstance->visitors.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<Visitor*>(&tdv), compositionInstance->visitors[0]);
}

void DefaultVisitorTest::compositionVisitsInstance()
{
  DefaultVisitorMock tdv;

  composition->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Composition"));
  CPPUNIT_ASSERT(tdv.hasVisited("Instance:instance"));
}

void DefaultVisitorTest::compositionVisitsConnection()
{
  DefaultVisitorMock tdv;

  composition->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Composition"));
  CPPUNIT_ASSERT(tdv.hasVisited("Connection:signal->slot"));
}

void DefaultVisitorTest::nullImplementationVisitsOnlyNullImplementation()
{
  DefaultVisitorMock tdv;

  componentNullImpl->getImplementation()->accept(tdv);

  CPPUNIT_ASSERT_EQUAL(test::sl({"NullImplementation"}), tdv.visited);
}

void DefaultVisitorTest::compositionInstance_visits_ports()
{
  DefaultVisitorMock tdv;

  CompositionInstance instance{componentNullImpl};
  instance.accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("CompositionInstance"));
  CPPUNIT_ASSERT(tdv.hasVisited("InstancePort:slot"));
  CPPUNIT_ASSERT(tdv.hasVisited("InstancePort:signal"));
}

void DefaultVisitorTest::componentVisitsPorts()
{
  DefaultVisitorMock tdv;

  componentNullImpl->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentNullImpl"));
  CPPUNIT_ASSERT(tdv.hasVisited("ComponentPort:signal"));
  CPPUNIT_ASSERT(tdv.hasVisited("ComponentPort:slot"));
}

void DefaultVisitorTest::componentVisitsImplementation()
{
  DefaultVisitorMock tdv;

  componentNullImpl->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentNullImpl"));
  CPPUNIT_ASSERT(tdv.hasVisited("NullImplementation"));
}

void DefaultVisitorTest::libraryVisitsComponents()
{
  DefaultVisitorMock tdv;

  library->accept(tdv);

  CPPUNIT_ASSERT(tdv.hasVisited("Library"));
  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentNullImpl"));
  CPPUNIT_ASSERT(tdv.hasVisited("Component:componentComposition"));
}

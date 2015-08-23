// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceTest.hpp"

#include <core/component/ComponentFactory.hpp>
#include <core/base/Position.hpp>
#include <core/Point.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/instance/AbstractInstance.hpp>

void InstanceTest::setUp()
{
  component = ComponentFactory::produce("Component", {"in1", "in2"}, {"out1"});
  instance = InstanceFactory::produce(component, "instance", Point(3, 7));
}

void InstanceTest::tearDown()
{
  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void InstanceTest::produce()
{
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), instance->getName());
  CPPUNIT_ASSERT_EQUAL(Point(3, 7), instance->getOffset());
  CPPUNIT_ASSERT_EQUAL(component, instance->getComponent());
  CPPUNIT_ASSERT(dynamic_cast<AbstractInstance*>(instance) != nullptr);
}

void InstanceTest::setPosition()
{
  CPPUNIT_ASSERT_EQUAL(Point( 3,  7), instance->getOffset());
  instance->setOffset(Point(57, 42));
  CPPUNIT_ASSERT_EQUAL(Point(57, 42), instance->getOffset());
}

void InstanceTest::updatePositionOnIndexChange()
{
  component->getPorts()[0]->setTopIndex(1);
  CPPUNIT_ASSERT_EQUAL(instance->getPorts()[1]->getPosition(), instance->getPorts()[0]->getPosition());
}

void InstanceTest::inheritsPosition()
{
  CPPUNIT_ASSERT(dynamic_cast<Position*>(instance) != nullptr);
}

void InstanceTest::inheritsBase()
{
  CPPUNIT_ASSERT(dynamic_cast<Base*>(instance) != nullptr);
}

void InstanceTest::getPortWithExisting()
{
  InstancePort *in2 = instance->getPort("in2");
  InstancePort *out1 = instance->getPort("out1");
  InstancePort *in1 = instance->getPort("in1");

  CPPUNIT_ASSERT(in1 != nullptr);
  CPPUNIT_ASSERT(in2 != nullptr);
  CPPUNIT_ASSERT(out1 != nullptr);

  CPPUNIT_ASSERT(in1 != in2);
  CPPUNIT_ASSERT(in1 != out1);
  CPPUNIT_ASSERT(in2 != out1);
}

void InstanceTest::getPortForNonExistingThrowsError()
{
  CPPUNIT_ASSERT_THROW(instance->getPort("lala"), std::invalid_argument);
}

void InstanceTest::addPortWhenComponentPortIsAdded()
{
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  component->addPort(new Slot("newSlot"));
  CPPUNIT_ASSERT_EQUAL(size_t(4), instance->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("newSlot"), instance->getPorts().back()->getName());
}

void InstanceTest::deletePortWhenComponentPortIsDeleted()
{
  ComponentPort *compPort = component->getPorts()[0];
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  component->deletePort(compPort);
  CPPUNIT_ASSERT_EQUAL(size_t(2), instance->getPorts().size());
}

void InstanceTest::deletePortWhenComponentHasPortsWithSameName()
{
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  InstancePort *port1 = instance->getPorts()[2];
  Signal *sig = new Signal("out1");
  component->addPort(sig);
  CPPUNIT_ASSERT_EQUAL(size_t(4), instance->getPorts().size());
  InstancePort *port2 = instance->getPorts()[3];
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), port1->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), port2->getName());

  component->deletePort(sig);
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(port1, instance->getPorts()[2]);
}

void InstanceTest::updatePortPositionsOnPortDelete()
{
  const Point pos0 = instance->getPort("in1")->getPosition();
  component->deletePort(component->getPort("in1"));
  CPPUNIT_ASSERT_EQUAL(pos0, instance->getPort("in2")->getPosition());
}

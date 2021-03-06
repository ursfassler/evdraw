// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceTest.hpp"

#include <core/component/ComponentFactory.hpp>
#include <core/base/Position.hpp>
#include <core/Point.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/instance/IInstance.hpp>

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
  CPPUNIT_ASSERT_EQUAL(Point(3, 7), instance->getPosition().getOffset());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<IComponent*>(component), instance->getComponent());
  CPPUNIT_ASSERT(dynamic_cast<IInstance*>(instance) != nullptr);
}

void InstanceTest::setPosition()
{
  CPPUNIT_ASSERT_EQUAL(Point( 3,  7), instance->getPosition().getOffset());
  instance->getPosition().setOffset(Point(57, 42));
  CPPUNIT_ASSERT_EQUAL(Point(57, 42), instance->getPosition().getOffset());
}

void InstanceTest::updatePositionOnIndexChange()
{
  component->getPorts()[0]->setTopIndex(1);
  CPPUNIT_ASSERT_EQUAL(instance->getPorts()[1]->getPosition().getAbsolutePosition(), instance->getPorts()[0]->getPosition().getAbsolutePosition());
}

void InstanceTest::has_position()
{
  const auto &position = instance->getPosition();
  CPPUNIT_ASSERT_EQUAL(Point(3,7), position.getAbsolutePosition());
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
  component->getPorts().add(new ComponentPort("newSlot", PortType::Slot));
  CPPUNIT_ASSERT_EQUAL(size_t(4), instance->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("newSlot"), instance->getPorts().back()->getName());
}

void InstanceTest::deletePortWhenComponentPortIsDeleted()
{
  ComponentPort *compPort = component->getPorts()[0];
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  component->getPorts().remove(compPort);
  CPPUNIT_ASSERT_EQUAL(size_t(2), instance->getPorts().size());
}

void InstanceTest::deletePortWhenComponentHasPortsWithSameName()
{
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  InstancePort *port1 = instance->getPorts()[2];
  ComponentPort *sig = new ComponentPort("out1", PortType::Signal);
  component->getPorts().add(sig);
  CPPUNIT_ASSERT_EQUAL(size_t(4), instance->getPorts().size());
  InstancePort *port2 = instance->getPorts()[3];
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), port1->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), port2->getName());

  component->getPorts().remove(sig);
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(port1, instance->getPorts()[2]);
}

void InstanceTest::setName()
{
  instance->setName("new name");
  CPPUNIT_ASSERT_EQUAL(std::string("new name"), instance->getName());
}

void InstanceTest::updatePortPositionsOnPortDelete()
{
  const Point pos0 = instance->getPort("in1")->getPosition().getAbsolutePosition();
  component->getPorts().remove(component->getPort("in1"));
  CPPUNIT_ASSERT_EQUAL(pos0, instance->getPort("in2")->getPosition().getAbsolutePosition());
}

void InstanceTest::connector_side_of_slot_is_left()
{
  CPPUNIT_ASSERT_EQUAL(Side::Left, instance->connectorSide(PortType::Slot));
}

void InstanceTest::connector_side_of_signal_is_right()
{
  CPPUNIT_ASSERT_EQUAL(Side::Right, instance->connectorSide(PortType::Signal));
}

void InstanceTest::dimension_is_not_zero()
{
  CPPUNIT_ASSERT(instance->getWidth() > 0);
  CPPUNIT_ASSERT(instance->getHeight() > 0);
}

void InstanceTest::height_depends_on_ports()
{
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(3, 7));

  PaperUnit height0 = instance->getHeight();

  component->getPorts().add(new ComponentPort("", PortType::Slot));
  PaperUnit height1 = instance->getHeight();
  CPPUNIT_ASSERT(height1 > height0);

  component->getPorts().add(new ComponentPort("", PortType::Slot));
  PaperUnit height2 = instance->getHeight();
  CPPUNIT_ASSERT(height2 > height1);

  component->getPorts().add(new ComponentPort("", PortType::Signal));
  PaperUnit height2a = instance->getHeight();
  CPPUNIT_ASSERT_EQUAL(height2, height2a);

  component->getPorts().add(new ComponentPort("", PortType::Signal));
  PaperUnit height2b = instance->getHeight();
  CPPUNIT_ASSERT_EQUAL(height2, height2b);

  component->getPorts().add(new ComponentPort("", PortType::Signal));
  PaperUnit height3 = instance->getHeight();
  CPPUNIT_ASSERT(height3 > height2);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

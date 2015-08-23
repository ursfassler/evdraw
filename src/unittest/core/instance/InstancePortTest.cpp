// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstancePortTest.hpp"

#include <core/component/ComponentPort.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>

#include <core/instance/InstancePortFactory.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/instance/InstanceFactory.hpp>

void InstancePortTest::createPort()
{
  Component *comp = ComponentFactory::produce("", {"bla"}, {});
  ComponentPort *cport = comp->getPorts()[0];

  Instance *inst = InstanceFactory::produce(comp, "inst", Point(0,0));
  InstancePort *port = InstancePortFactory::produce(inst, cport);

  CPPUNIT_ASSERT_EQUAL(std::string("bla"), port->getCompPort()->getName());
  CPPUNIT_ASSERT(port->getConnector().getOffset().x < 0);
  CPPUNIT_ASSERT_EQUAL(0, port->getConnector().getOffset().y);
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractInstance*>(inst), port->getInstance());

  InstancePortFactory::dispose(port);
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::offset()
{
  Component *comp = ComponentFactory::produce("", {"1", "2"}, {});
  ComponentPort *cport1 = comp->getPorts()[0];
  ComponentPort *cport2 = comp->getPorts()[1];

  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port1 = InstancePortFactory::produce(inst, cport1);
  InstancePort *port2 = InstancePortFactory::produce(inst, cport2);

  CPPUNIT_ASSERT(port1->getOffset().x < 0);
  CPPUNIT_ASSERT(port1->getOffset().y > 0);

  CPPUNIT_ASSERT_EQUAL(port2->getOffset().x, port1->getOffset().x);
  CPPUNIT_ASSERT(port2->getOffset().y > port1->getOffset().y);

  InstancePortFactory::dispose(port2);
  InstancePortFactory::dispose(port1);
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::absolutePosition()
{
  Component *comp = ComponentFactory::produce("", {"bla"}, {});
  ComponentPort *cport = comp->getPorts()[0];

  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = InstancePortFactory::produce(inst, cport);

  CPPUNIT_ASSERT(port->getAbsolutePosition().x < 0);
  CPPUNIT_ASSERT(port->getAbsolutePosition().y > 0);

  InstancePortFactory::dispose(port);
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::positionChangeNotificationNotifiesConnector()
{
  Component *comp = ComponentFactory::produce("", {"left"}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = InstancePortFactory::produce(inst, comp->getPorts()[0]);

  Point pos = port->getConnector().getAbsolutePosition();
  inst->setOffset(Point(10,20));

  CPPUNIT_ASSERT_EQUAL(pos+Point(10,20), port->getConnector().getAbsolutePosition());

  InstancePortFactory::dispose(port);
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::portIsLeft()
{
  Component *comp = ComponentFactory::produce("", {"left"}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = InstancePortFactory::produce(inst, comp->getPorts()[0]);

  CPPUNIT_ASSERT_EQUAL(Side::Left, port->side());

  InstancePortFactory::dispose(port);
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::portIsRight()
{
  Component *comp = ComponentFactory::produce("", {}, {"right"});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = InstancePortFactory::produce(inst, comp->getPorts()[0]);

  CPPUNIT_ASSERT_EQUAL(Side::Right, port->side());

  InstancePortFactory::dispose(port);
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::setName()
{
  Component *comp = ComponentFactory::produce("", {}, {"right"});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = InstancePortFactory::produce(inst, comp->getPorts()[0]);

  port->setName("test name");
  CPPUNIT_ASSERT_EQUAL(std::string("test name"), port->getName());

  InstancePortFactory::dispose(port);
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

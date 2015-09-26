// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstancePortTest.hpp"

#include <core/component/ComponentPort.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>

#include <core/instance/InstancePort.hpp>
#include <core/instance/InstanceFactory.hpp>

void InstancePortTest::createPort()
{
  Component *comp = ComponentFactory::produce("", {"bla"}, {});
  ComponentPort *cport = comp->getPorts()[0];

  Instance *inst = InstanceFactory::produce(comp, "inst", Point(0,0));
  InstancePort *port = new InstancePort(inst, cport);

  CPPUNIT_ASSERT_EQUAL(std::string("bla"), port->getCompPort()->getName());
  CPPUNIT_ASSERT(port->getConnector().getOffset().x < 0);
  CPPUNIT_ASSERT_EQUAL(0, port->getConnector().getOffset().y);
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<IInstance*>(inst), port->getInstance());
  CPPUNIT_ASSERT(!port->hasAnchor());

  delete port;
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::offset()
{
  Component *comp = ComponentFactory::produce("", {"1", "2"}, {"3"});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port1 = inst->getPorts()[0];
  InstancePort *port2 = inst->getPorts()[1];
  InstancePort *port3 = inst->getPorts()[2];

  CPPUNIT_ASSERT(port1->getOffset().x < 0);
  CPPUNIT_ASSERT(port1->getOffset().y > 0);
  CPPUNIT_ASSERT(port3->getOffset().x > 0);

  CPPUNIT_ASSERT_EQUAL(port2->getOffset().x, port1->getOffset().x);
  CPPUNIT_ASSERT(port2->getOffset().y > port1->getOffset().y);
  CPPUNIT_ASSERT_EQUAL(port1->getOffset().y, port3->getOffset().y);

  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::absolutePosition()
{
  Component *comp = ComponentFactory::produce("", {"bla"}, {});
  ComponentPort *cport = comp->getPorts()[0];

  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = new InstancePort(inst, cport);

  CPPUNIT_ASSERT(port->getAbsolutePosition().x < 0);
  CPPUNIT_ASSERT(port->getAbsolutePosition().y > 0);

  delete port;
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::position_change_notification_notifies_connector()
{
  Component *comp = ComponentFactory::produce("", {"left"}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = new InstancePort(inst, comp->getPorts()[0]);
  port->replaceAnchor(inst);

  Point pos = port->getConnector().getAbsolutePosition();
  inst->setOffset(Point(10,20));

  CPPUNIT_ASSERT_EQUAL(pos+Point(10,20), port->getConnector().getAbsolutePosition());

  delete port;
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::port_is_Slot()
{
  Component *comp = ComponentFactory::produce("", {"left"}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = new InstancePort(inst, comp->getPorts()[0]);

  CPPUNIT_ASSERT_EQUAL(PortType::Slot, port->getType());

  delete port;
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::port_is_Signal()
{
  Component *comp = ComponentFactory::produce("", {}, {"right"});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = new InstancePort(inst, comp->getPorts()[0]);

  CPPUNIT_ASSERT_EQUAL(PortType::Signal, port->getType());

  delete port;
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::type_change_changes_position()
{
  Component *comp = ComponentFactory::produce("", {""}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  ComponentPort *compPort = comp->getPorts()[0];
  InstancePort *port = new InstancePort(inst, compPort);

  CPPUNIT_ASSERT(port->getOffset().x < 0);
  compPort->setType(PortType::Signal);
  CPPUNIT_ASSERT(port->getOffset().x > 0);

  delete port;
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::type_change_notifies_connector()
{
  Component *comp = ComponentFactory::produce("", {"left"}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = new InstancePort(inst, comp->getPorts()[0]);

  CPPUNIT_ASSERT(port->getConnector().getOffset().x < 0);
  port->getCompPort()->setType(PortType::Signal);
  CPPUNIT_ASSERT(port->getConnector().getOffset().x > 0);

  delete port;
  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::addConnectionPoint_sets_position()
{
  Component *comp = ComponentFactory::produce("", {"left"}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = inst->getPorts()[0];
  RelativePosition pos(Point(0,0));

  port->addConnectionPoint(&pos);

  CPPUNIT_ASSERT(pos.getAbsolutePosition().x < 0);
  CPPUNIT_ASSERT(pos.getAbsolutePosition().y > 0);

  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::removeConnectionPoint_changes_position_of_others()
{
  Component *comp = ComponentFactory::produce("", {"left"}, {});
  Instance *inst = InstanceFactory::produce(comp, "", Point(0, 0));
  InstancePort *port = inst->getPorts()[0];
  RelativePosition pos1(Point(0,0));
  RelativePosition pos2(Point(0,0));
  port->addConnectionPoint(&pos1);
  const Point point1 = pos1.getAbsolutePosition();
  port->addConnectionPoint(&pos2);
  port->removeConnectionPoint(&pos2);

  CPPUNIT_ASSERT_EQUAL(point1, pos1.getAbsolutePosition());

  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

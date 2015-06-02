#include "InstancePortTest.hpp"

#include "../component/ComponentPort.hpp"
#include "../component/ComponentFactory.hpp"
#include "../connection/Connection.hpp"
#include "../connection/ConnectionFactory.hpp"

#include "InstancePortFactory.hpp"
#include "InstancePort.hpp"

void InstancePortTest::createPort()
{
  Component *comp = ComponentFactory::produce("", {"bla"}, {});
  ComponentPort *cport = comp->getPortLeft()[0];

  Instance inst("", Point(0, 0), comp);
  InstancePort *port = InstancePortFactory::produce(&inst, cport);

  CPPUNIT_ASSERT_EQUAL(std::string("bla"), port->getCompPort()->getName());
  CPPUNIT_ASSERT(port->getConnector().getOffset().x < 0);
  CPPUNIT_ASSERT_EQUAL(0, port->getConnector().getOffset().y);

  InstancePortFactory::dispose(port);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::offset()
{
  Component *comp = ComponentFactory::produce("", {"1", "2"}, {});
  ComponentPort *cport1 = comp->getPortLeft()[0];
  ComponentPort *cport2 = comp->getPortLeft()[1];

  Instance inst("", Point(0, 0), comp);
  InstancePort *port1 = InstancePortFactory::produce(&inst, cport1);
  InstancePort *port2 = InstancePortFactory::produce(&inst, cport2);

  CPPUNIT_ASSERT(port1->getOffset().x < 0);
  CPPUNIT_ASSERT(port1->getOffset().y > 0);

  CPPUNIT_ASSERT_EQUAL(port2->getOffset().x, port1->getOffset().x);
  CPPUNIT_ASSERT(port2->getOffset().y > port1->getOffset().y);

  InstancePortFactory::dispose(port2);
  InstancePortFactory::dispose(port1);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::absolutePosition()
{
  Component *comp = ComponentFactory::produce("", {"bla"}, {});
  ComponentPort *cport = comp->getPortLeft()[0];

  Instance inst("", Point(0, 0), comp);
  InstancePort *port = InstancePortFactory::produce(&inst, cport);

  CPPUNIT_ASSERT(port->getAbsolutePosition().x < 0);
  CPPUNIT_ASSERT(port->getAbsolutePosition().y > 0);

  InstancePortFactory::dispose(port);
  ComponentFactory::dispose(comp);
}

void InstancePortTest::positionChangeNotificationNotifiesConnector()
{
  Component *comp = ComponentFactory::produce("", {}, {});
  Instance inst("", Point(0, 0), comp);
  InstancePort port(&inst, nullptr, Point(0,0));

  inst.setOffset(Point(10,20));

  CPPUNIT_ASSERT_EQUAL(Point(10,20), port.getConnector().getAbsolutePosition());
}

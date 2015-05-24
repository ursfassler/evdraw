#include "InstancePortTest.hpp"

#include "../component/ComponentPort.hpp"
#include "../connection/Connection.hpp"
#include "../connection/ConnectionFactory.hpp"

#include "InstancePortFactory.hpp"
#include "InstancePort.hpp"

void InstancePortTest::createPort()
{
  Component comp;
  ComponentPort cport("bla");
  comp.addPortLeft(&cport);

  Instance inst(Point(0, 0), &comp);
  InstancePort *port = InstancePortFactory::produce(cport, inst);

  CPPUNIT_ASSERT_EQUAL(std::string("bla"), port->getCompPort().getName());
  CPPUNIT_ASSERT(port->getConnector().getOffset().x < 0);

  InstancePortFactory::dispose(port);
}

void InstancePortTest::position()
{
  Component comp;

  ComponentPort cport1("1");
  comp.addPortLeft(&cport1);
  ComponentPort cport2("2");
  comp.addPortLeft(&cport2);

  Instance inst(Point(0, 0), &comp);
  InstancePort *port1 = InstancePortFactory::produce(cport1, inst);
  InstancePort *port2 = InstancePortFactory::produce(cport2, inst);

  CPPUNIT_ASSERT(port1->getOffset().x < 0);
  CPPUNIT_ASSERT(port1->getOffset().y > 0);

  CPPUNIT_ASSERT_EQUAL(port2->getOffset().x, port1->getOffset().x);
  CPPUNIT_ASSERT(port2->getOffset().y > port1->getOffset().y);

  InstancePortFactory::dispose(port2);
  InstancePortFactory::dispose(port1);
}

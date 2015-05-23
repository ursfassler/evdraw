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

  InstancePortFactory::dispose(port);
}

void InstancePortTest::position()
{
  Component comp;
  ComponentPort cport("");
  comp.addPortLeft(&cport);

  Instance inst(Point(0, 0), &comp);
  InstancePort *port = InstancePortFactory::produce(cport, inst);

  CPPUNIT_ASSERT(port->getOffset().x < 0);
  CPPUNIT_ASSERT(port->getOffset().y > 0);

  InstancePortFactory::dispose(port);
}

//void InstancePortTest::addConnection()
//{
//  ComponentPort cportA("");
//  ComponentPort cportB("");
//  InstancePort a(cportA, Point(-20, 0), ConnectorSide::Right);
//  InstancePort b(cportB, Point( 20, 0), ConnectorSide::Left);

//  Connection *con = ConnectionFactory::produce(0, 0, 0, 0);

//  CPPUNIT_ASSERT_EQUAL(size_t(0), a.getConnections().size());
//  CPPUNIT_ASSERT_EQUAL(size_t(0), b.getConnections().size());

//  a.addConnection(con);
//  CPPUNIT_ASSERT_EQUAL(size_t(1), a.getConnections().size());
//  CPPUNIT_ASSERT_EQUAL(con, a.getConnections()[0]);

//  b.addConnection(con);
//  CPPUNIT_ASSERT_EQUAL(size_t(1), b.getConnections().size());
//  CPPUNIT_ASSERT_EQUAL(con, b.getConnections()[0]);
//}

//void InstancePortTest::connectionPosRight()
//{
//  ComponentPort cport("");
//  InstancePort port(cport, ConnectorSide::Right);

//  Connection *con = ConnectionFactory::produce(0, 0, 0, 0);
//  port.addConnection(con);

//  CPPUNIT_ASSERT_EQUAL(ConnectorSide::Right, port.getConnectorSide());
//  CPPUNIT_ASSERT_EQUAL(-20, con->getStart().getX());
//  CPPUNIT_ASSERT_EQUAL(-10, con->getStart().getY());
//  CPPUNIT_ASSERT_EQUAL(  0, con->getEnd().getX());
//  CPPUNIT_ASSERT_EQUAL(  0, con->getEnd().getY());
//}

//void InstancePortTest::connectionPosLeft()
//{
//  ComponentPort cport("");
//  InstancePort port(cport, Point(-25, -15), ConnectorSide::Left);

//  Connection *con = ConnectionFactory::produce(0, 0, 0, 0);
//  port.addConnection(con);

//  CPPUNIT_ASSERT_EQUAL(ConnectorSide::Left, port.getConnectorSide());
//  CPPUNIT_ASSERT_EQUAL(-25, con->getEnd().getX());
//  CPPUNIT_ASSERT_EQUAL(-15, con->getEnd().getY());
//  CPPUNIT_ASSERT_EQUAL(  0, con->getStart().getX());
//  CPPUNIT_ASSERT_EQUAL(  0, con->getStart().getY());
//}


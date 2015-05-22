#include "InstancePortTest.hpp"

#include <core/InstancePort.hpp>
#include <core/Connection.hpp>
#include <core/ConnectionFactory.hpp>

void InstancePortTest::createPort()
{
  InstancePort port(0, 0, InstancePort::ConnectorSide::Left);
}

void InstancePortTest::position()
{
  InstancePort port(42, 57, InstancePort::ConnectorSide::Left);

  CPPUNIT_ASSERT_EQUAL(42, port.getX());
  CPPUNIT_ASSERT_EQUAL(57, port.getY());
}

void InstancePortTest::size()
{
  InstancePort port(0, 0, InstancePort::ConnectorSide::Left);

  CPPUNIT_ASSERT(port.getHeight() > 0);
}

void InstancePortTest::addConnection()
{
  InstancePort a(-20, 0, InstancePort::ConnectorSide::Right);
  InstancePort b( 20, 0, InstancePort::ConnectorSide::Left);

  Connection *con = ConnectionFactory::produce(0, 0, 0, 0);

  CPPUNIT_ASSERT_EQUAL(size_t(0), a.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), b.getConnections().size());

  a.addConnection(con);
  CPPUNIT_ASSERT_EQUAL(size_t(1), a.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(con, a.getConnections()[0]);

  b.addConnection(con);
  CPPUNIT_ASSERT_EQUAL(size_t(1), b.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(con, b.getConnections()[0]);
}

void InstancePortTest::connectionPosRight()
{
  InstancePort port(-20, -10, InstancePort::ConnectorSide::Right);

  Connection *con = ConnectionFactory::produce(0, 0, 0, 0);
  port.addConnection(con);

  CPPUNIT_ASSERT_EQUAL(InstancePort::ConnectorSide::Right, port.getConnectorSide());
  CPPUNIT_ASSERT_EQUAL(-20, con->getStart().getX());
  CPPUNIT_ASSERT_EQUAL(-10, con->getStart().getY());
  CPPUNIT_ASSERT_EQUAL(  0, con->getEnd().getX());
  CPPUNIT_ASSERT_EQUAL(  0, con->getEnd().getY());
}

void InstancePortTest::connectionPosLeft()
{
  InstancePort port(-25, -15, InstancePort::ConnectorSide::Left);

  Connection *con = ConnectionFactory::produce(0, 0, 0, 0);
  port.addConnection(con);

  CPPUNIT_ASSERT_EQUAL(InstancePort::ConnectorSide::Left, port.getConnectorSide());
  CPPUNIT_ASSERT_EQUAL(-25, con->getEnd().getX());
  CPPUNIT_ASSERT_EQUAL(-15, con->getEnd().getY());
  CPPUNIT_ASSERT_EQUAL(  0, con->getStart().getX());
  CPPUNIT_ASSERT_EQUAL(  0, con->getStart().getY());
}


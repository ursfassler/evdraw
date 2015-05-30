#include "ConnectorTest.hpp"

#include "Connector.hpp"
#include "../component/InstanceAppearance.hpp"
#include "../connection/Connection.hpp"
#include "../connection/ConnectionFactory.hpp"

void ConnectorTest::create()
{
  Connector connector(nullptr, Point(42, 57));
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), connector.getOffset());
  CPPUNIT_ASSERT(connector.getPoints().empty());
}

void ConnectorTest::addPortPoint()
{
  Connector connector(nullptr, Point(42, 57));
  PortPoint pp(Point(0, 0));

  CPPUNIT_ASSERT_EQUAL(size_t(0), connector.getPoints().size());

  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(size_t(1), connector.getPoints().size());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&pp), connector.getPoints()[0]);
}

void ConnectorTest::addPortPointUpdatesPosition()
{
  Connector connector(nullptr, Point(-10,-20));
  PortPoint pp(Point(20, 30));
  connector.addPoint(&pp);

  CPPUNIT_ASSERT_EQUAL(Point(-10,-20), pp.getPosition());
}

void ConnectorTest::positionOfPortIsWithinHeight()
{
  const PaperUnit top = -InstanceAppearance::portDimension().y/2;
  const PaperUnit bottom = InstanceAppearance::portDimension().y/2;

  Connector connector(nullptr, Point(0,0));
  PortPoint pp1(Point(0,0));
  PortPoint pp2(Point(0,0));
  PortPoint pp3(Point(0,0));
  PortPoint pp4(Point(0,0));

  connector.addPoint(&pp1);
  CPPUNIT_ASSERT_EQUAL(0, pp1.getPosition().y);

  connector.addPoint(&pp2);
  CPPUNIT_ASSERT(pp1.getPosition().y < 0);
  CPPUNIT_ASSERT(pp1.getPosition().y >= top);
  CPPUNIT_ASSERT(pp2.getPosition().y > 0);
  CPPUNIT_ASSERT(pp2.getPosition().y < bottom);

  connector.addPoint(&pp3);
  CPPUNIT_ASSERT(pp1.getPosition().y < 0);
  CPPUNIT_ASSERT(pp1.getPosition().y >= top);
  CPPUNIT_ASSERT_EQUAL(0, pp2.getPosition().y);
  CPPUNIT_ASSERT(pp3.getPosition().y > 0);
  CPPUNIT_ASSERT(pp3.getPosition().y < bottom);

  connector.addPoint(&pp4);
  CPPUNIT_ASSERT(pp1.getPosition().y >= top);
  CPPUNIT_ASSERT(pp1.getPosition().y < pp2.getPosition().y);
  CPPUNIT_ASSERT(pp2.getPosition().y < 0);
  CPPUNIT_ASSERT(pp3.getPosition().y > 0);
  CPPUNIT_ASSERT(pp4.getPosition().y > pp3.getPosition().y);
  CPPUNIT_ASSERT(pp4.getPosition().y < bottom);

}

void ConnectorTest::setNewOffset()
{
  Connector connector(nullptr, Point(23, 13));
  CPPUNIT_ASSERT_EQUAL(Point(23, 13), connector.getOffset());

  connector.setOffset(Point(42, 57));
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), connector.getOffset());
}

void ConnectorTest::setOffsetUpdatesPortPoint()
{
  Connector connector(nullptr, Point(0,0));
  PortPoint pp(Point(0,0));
  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(Point(0,0), pp.getPosition());

  connector.setOffset(Point(-4,15));
  CPPUNIT_ASSERT_EQUAL(Point(-4,15), pp.getPosition());
}

void ConnectorTest::notificationUpdatesPortPoint()
{
  Base base(nullptr, Point(0,0));
  Connector connector(&base, Point(0,0));
  PortPoint pp(Point(0,0));
  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(Point(0,0), pp.getPosition());

  base.setOffset(Point(10,20));

  CPPUNIT_ASSERT_EQUAL(Point(10,20), pp.getPosition());
}

void ConnectorTest::addConnectionStart()
{
  Connector connector(nullptr, Point(42, 57));
  Connection *con = ConnectionFactory::produce(-10,-10,10,10);

  connector.addPoint(con->getStart());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connector.getPoints().size());
  CPPUNIT_ASSERT_EQUAL(con->getStart(), connector.getPoints()[0]);
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), con->getStart()->getPosition());
}

void ConnectorTest::addConnectionEnd()
{
  Connector connector(nullptr, Point(42, 57));
  Connection *con = ConnectionFactory::produce(-10,-10,10,10);

  connector.addPoint(con->getEnd());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connector.getPoints().size());
  CPPUNIT_ASSERT_EQUAL(con->getEnd(), connector.getPoints()[0]);
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), con->getEnd()->getPosition());
}

#include "ConnectorTest.hpp"

#include "Connector.hpp"
#include "../component/InstanceAppearance.hpp"

void ConnectorTest::create()
{
  Connector connector(Point(42, 57));
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), connector.getOffset());
  CPPUNIT_ASSERT(connector.getPoints().empty());
}

void ConnectorTest::addPortPoint()
{
  Connector connector(Point(42, 57));
  PortPoint pp(0, 0);

  CPPUNIT_ASSERT_EQUAL(size_t(0), connector.getPoints().size());

  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(size_t(1), connector.getPoints().size());
  CPPUNIT_ASSERT_EQUAL(&pp, connector.getPoints()[0]);
}

void ConnectorTest::addPortPointUpdatesPosition()
{
  Connector connector(Point(-10,-20));
  PortPoint pp(20, 30);
  connector.addPoint(&pp);

  CPPUNIT_ASSERT_EQUAL(-10, pp.getX());
  CPPUNIT_ASSERT_EQUAL(-20, pp.getY());
}

void ConnectorTest::positionOfPortIsWithinHeight()
{
  const PaperUnit top = -InstanceAppearance::portHeight()/2;
  const PaperUnit bottom = InstanceAppearance::portHeight()/2;

  Connector connector(Point(0,0));
  PortPoint pp1(0,0);
  PortPoint pp2(0,0);
  PortPoint pp3(0,0);
  PortPoint pp4(0,0);

  connector.addPoint(&pp1);
  CPPUNIT_ASSERT_EQUAL(0, pp1.getY());

  connector.addPoint(&pp2);
  CPPUNIT_ASSERT(pp1.getY() < 0);
  CPPUNIT_ASSERT(pp1.getY() >= top);
  CPPUNIT_ASSERT(pp2.getY() > 0);
  CPPUNIT_ASSERT(pp2.getY() < bottom);

  connector.addPoint(&pp3);
  CPPUNIT_ASSERT(pp1.getY() < 0);
  CPPUNIT_ASSERT(pp1.getY() >= top);
  CPPUNIT_ASSERT_EQUAL(0, pp2.getY());
  CPPUNIT_ASSERT(pp3.getY() > 0);
  CPPUNIT_ASSERT(pp3.getY() < bottom);

  connector.addPoint(&pp4);
  CPPUNIT_ASSERT(pp1.getY() >= top);
  CPPUNIT_ASSERT(pp1.getY() < pp2.getY());
  CPPUNIT_ASSERT(pp2.getY() < 0);
  CPPUNIT_ASSERT(pp3.getY() > 0);
  CPPUNIT_ASSERT(pp4.getY() > pp3.getY());
  CPPUNIT_ASSERT(pp4.getY() < bottom);

}

void ConnectorTest::setNewOffset()
{
  Connector connector(Point(23, 13));
  CPPUNIT_ASSERT_EQUAL(Point(23, 13), connector.getOffset());

  connector.setOffset(Point(42, 57));
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), connector.getOffset());
}

void ConnectorTest::setOffsetUpdatesPortPoint()
{
  Connector connector(Point(0,0));
  PortPoint pp(0,0);
  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(0, pp.getX());
  CPPUNIT_ASSERT_EQUAL(0, pp.getY());

  connector.setOffset(Point(-4,15));
  CPPUNIT_ASSERT_EQUAL(-4, pp.getX());
  CPPUNIT_ASSERT_EQUAL(15, pp.getY());
}


#include "ConnectorTest.hpp"

#include "Connector.hpp"
#include "../component/InstanceAppearance.hpp"
#include "../connection/Connection.hpp"
#include "../connection/ConnectionFactory.hpp"

void ConnectorTest::create()
{
  Connector connector(Point(42, 57));
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), connector.getOffset());
  CPPUNIT_ASSERT(connector.getPoints().empty());
}

void ConnectorTest::addPortPoint()
{
  Connector connector(Point(42, 57));
  RelativePosition pp(Point(0, 0));

  CPPUNIT_ASSERT_EQUAL(size_t(0), connector.getPoints().size());

  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(size_t(1), connector.getPoints().size());
  CPPUNIT_ASSERT_EQUAL(&pp, connector.getPoints()[0]);
}

void ConnectorTest::addPortPointUpdatesPosition()
{
  Connector connector(Point(-10,-20));
  RelativePosition pp(Point(20, 30));
  connector.addPoint(&pp);

  CPPUNIT_ASSERT_EQUAL(Point(-10,-20), pp.getAbsolutePosition());
}

void ConnectorTest::positionOfPortIsWithinHeight()
{
  const PaperUnit top = -InstanceAppearance::portDimension().y/2;
  const PaperUnit bottom = InstanceAppearance::portDimension().y/2;

  Connector connector(Point(0,0));
  RelativePosition pp1(Point(0,0));
  RelativePosition pp2(Point(0,0));
  RelativePosition pp3(Point(0,0));
  RelativePosition pp4(Point(0,0));

  connector.addPoint(&pp1);
  CPPUNIT_ASSERT_EQUAL(0, pp1.getAbsolutePosition().y);

  connector.addPoint(&pp2);
  CPPUNIT_ASSERT(pp1.getAbsolutePosition().y < 0);
  CPPUNIT_ASSERT(pp1.getAbsolutePosition().y >= top);
  CPPUNIT_ASSERT(pp2.getAbsolutePosition().y > 0);
  CPPUNIT_ASSERT(pp2.getAbsolutePosition().y < bottom);

  connector.addPoint(&pp3);
  CPPUNIT_ASSERT(pp1.getAbsolutePosition().y < 0);
  CPPUNIT_ASSERT(pp1.getAbsolutePosition().y >= top);
  CPPUNIT_ASSERT_EQUAL(0, pp2.getAbsolutePosition().y);
  CPPUNIT_ASSERT(pp3.getAbsolutePosition().y > 0);
  CPPUNIT_ASSERT(pp3.getAbsolutePosition().y < bottom);

  connector.addPoint(&pp4);
  CPPUNIT_ASSERT(pp1.getAbsolutePosition().y >= top);
  CPPUNIT_ASSERT(pp1.getAbsolutePosition().y < pp2.getAbsolutePosition().y);
  CPPUNIT_ASSERT(pp2.getAbsolutePosition().y < 0);
  CPPUNIT_ASSERT(pp3.getAbsolutePosition().y > 0);
  CPPUNIT_ASSERT(pp4.getAbsolutePosition().y > pp3.getAbsolutePosition().y);
  CPPUNIT_ASSERT(pp4.getAbsolutePosition().y < bottom);

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
  RelativePosition pp(Point(0,0));
  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(Point(0,0), pp.getAbsolutePosition());

  connector.setOffset(Point(-4,15));
  CPPUNIT_ASSERT_EQUAL(Point(-4,15), pp.getAbsolutePosition());
}

void ConnectorTest::notificationUpdatesPortPoint()
{
  RelativePosition base(Point(0,0));
  Connector connector(Point(0,0));
  connector.replaceAnchor(&base);
  RelativePosition pp(Point(0,0));
  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(Point(0,0), pp.getAbsolutePosition());

  base.setOffset(Point(10,20));

  CPPUNIT_ASSERT_EQUAL(Point(10,20), pp.getAbsolutePosition());
}

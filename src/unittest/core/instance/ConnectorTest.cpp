// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectorTest.hpp"

#include <core/instance/Connector.hpp>
#include <core/instance/ConnectorFactory.hpp>
#include <core/component/InstanceAppearance.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>

void ConnectorTest::create()
{
  Connector connector(Point(42, 57));
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), connector.getPosition().getOffset());
  CPPUNIT_ASSERT(connector.getPoints().empty());

  ConnectorFactory::cleanup(connector);
}

void ConnectorTest::addPortPoint()
{
  Connector connector(Point(42, 57));
  RelativePosition pp(Point(0, 0));

  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(size_t(1), connector.getPoints().size());
  CPPUNIT_ASSERT_EQUAL(&pp, connector.getPoints()[0]);
  CPPUNIT_ASSERT_EQUAL(static_cast<IPosition*>(&connector.getPosition()), pp.getAnchor());

  ConnectorFactory::cleanup(connector);
}

void ConnectorTest::addPortPointUpdatesPosition()
{
  Connector connector(Point(-10,-20));
  RelativePosition pp(Point(20, 30));
  connector.addPoint(&pp);

  CPPUNIT_ASSERT_EQUAL(Point(-10,-20), pp.getAbsolutePosition());

  ConnectorFactory::cleanup(connector);
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

  ConnectorFactory::cleanup(connector);
}

void ConnectorTest::removePortPoint()
{
  Connector connector(Point(42, 57));
  RelativePosition pp(Point(0, 0));

  connector.addPoint(&pp);
  connector.removePoint(&pp);

  CPPUNIT_ASSERT_EQUAL(size_t(0), connector.getPoints().size());

  ConnectorFactory::cleanup(connector);
}

void ConnectorTest::removePortPointUpdatesPosition()
{
  Connector connector(Point(-10,-20));
  RelativePosition pp1(Point(20, 30));
  RelativePosition pp2(Point(20, 30));
  connector.addPoint(&pp1);
  const Point pos1 = pp1.getAbsolutePosition();
  connector.addPoint(&pp2);
  CPPUNIT_ASSERT(pos1 != pp1.getAbsolutePosition());
  connector.removePoint(&pp2);

  CPPUNIT_ASSERT_EQUAL(pos1, pp1.getAbsolutePosition());

  ConnectorFactory::cleanup(connector);
}

void ConnectorTest::setNewOffset()
{
  Connector connector(Point(23, 13));
  CPPUNIT_ASSERT_EQUAL(Point(23, 13), connector.getPosition().getOffset());

  connector.getPosition().setOffset(Point(42, 57));
  CPPUNIT_ASSERT_EQUAL(Point(42, 57), connector.getPosition().getOffset());

  ConnectorFactory::cleanup(connector);
}

void ConnectorTest::setOffsetUpdatesPortPoint()
{
  Connector connector(Point(0,0));
  RelativePosition pp(Point(0,0));
  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(Point(0,0), pp.getAbsolutePosition());

  connector.getPosition().setOffset(Point(-4,15));
  CPPUNIT_ASSERT_EQUAL(Point(-4,15), pp.getAbsolutePosition());

  ConnectorFactory::cleanup(connector);
}

void ConnectorTest::notificationUpdatesPortPoint()
{
  RelativePosition base(Point(0,0));
  Connector connector(Point(0,0));
  connector.getPosition().replaceAnchor(&base);
  RelativePosition pp(Point(0,0));
  connector.addPoint(&pp);
  CPPUNIT_ASSERT_EQUAL(Point(0,0), pp.getAbsolutePosition());

  base.setOffset(Point(10,20));

  CPPUNIT_ASSERT_EQUAL(Point(10,20), pp.getAbsolutePosition());

  ConnectorFactory::cleanup(connector);
}

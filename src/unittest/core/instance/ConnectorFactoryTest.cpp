// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectorFactoryTest.hpp"

#include <core/instance/ConnectorFactory.hpp>
#include <core/instance/Connector.hpp>

void ConnectorFactoryTest::cleanup_removes_points()
{
  Connector connector(Point(42, 57));
  RelativePosition pp(Point(0, 0));
  connector.addPoint(&pp);

  ConnectorFactory::cleanup(connector);

  CPPUNIT_ASSERT_EQUAL(size_t(0), connector.getPoints().size());
  CPPUNIT_ASSERT(&connector != pp.getAnchor());
}

void ConnectorFactoryTest::dispose_removes_points()
{
  Connector *connector = new Connector(Point(42, 57));
  RelativePosition pp(Point(0, 0));

  connector->addPoint(&pp);

  ConnectorFactory::dispose(connector);

  CPPUNIT_ASSERT(connector != pp.getAnchor());
}

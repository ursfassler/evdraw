// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionFactoryTest.hpp"

#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/connection/Segment.hpp>
#include <core/connection/SimplePort.hpp>
#include <core/connection/DrawPort.hpp>

#include <core/util/contract.hpp>

void ConnectionFactoryTest::createPointListWithOnlyOneElement()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::createPointList({0}), PreconditionError);
}

void ConnectionFactoryTest::createMinimalPointList()
{
  std::vector<Endpoint *> list = ConnectionFactory::createPointList({1, 2});

  CPPUNIT_ASSERT_EQUAL(size_t(1), list.size());
  CPPUNIT_ASSERT_EQUAL(Point(1,2), list[0]->getOffset());

  delete list[0];
}

void ConnectionFactoryTest::createSimplePointList()
{
  std::vector<Endpoint *> list = ConnectionFactory::createPointList({1, 2, 3, 4, 5});

  CPPUNIT_ASSERT_EQUAL(size_t(4), list.size());
  CPPUNIT_ASSERT_EQUAL(Point(1,2), list[0]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(3,2), list[1]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(3,4), list[2]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(5,4), list[3]->getOffset());

  delete list[0];
  delete list[1];
  delete list[2];
  delete list[3];
}

void ConnectionFactoryTest::cleanup()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);
  ConnectionFactory::cleanup(connection);
}

void ConnectionFactoryTest::canNotDisposeNullptr()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::dispose(nullptr), PreconditionError);
}

void ConnectionFactoryTest::createEmptyConnection()
{
  SimplePort startPort;
  SimplePort endPort;
  std::vector<PaperUnit> empty;
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce(&startPort, &endPort, empty), PreconditionError);
}

void ConnectionFactoryTest::createConnection()
{
  SimplePort startPort(Point(10,20));
  SimplePort endPort(Point(50,70));
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(30, connection->getVerticalSegment().front()->getX());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<IPort*>(&startPort), connection->getStartPort());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<IPort*>(&endPort), connection->getEndPort());
  CPPUNIT_ASSERT(startPort.ports.find(connection->getPoints().front()) != startPort.ports.end());
  CPPUNIT_ASSERT(endPort.ports.find(connection->getPoints().back()) != endPort.ports.end());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createPathConnection()
{
  SimplePort startPort(Point(-10, 3));
  SimplePort endPort(Point(7, -2));
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {-5, 4, 1});

  CPPUNIT_ASSERT_EQUAL(size_t(6), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(-10, 3), connection->getPoints()[0]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point( -5, 3), connection->getPoints()[1]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point( -5, 4), connection->getPoints()[2]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(  1, 4), connection->getPoints()[3]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(  1,-2), connection->getPoints()[4]->getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(  7,-2), connection->getPoints()[5]->getOffset());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getVerticalSegment()[0]->getX());
  CPPUNIT_ASSERT_EQUAL( 1, connection->getVerticalSegment()[1]->getX());

  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL( 3, connection->getHorizontalSegment()[0]->getY());
  CPPUNIT_ASSERT_EQUAL( 4, connection->getHorizontalSegment()[1]->getY());
  CPPUNIT_ASSERT_EQUAL(-2, connection->getHorizontalSegment()[2]->getY());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createConstruction()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produceConstruction(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<IPort*>(&startPort), connection->getStartPort());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<IPort*>(&endPort), connection->getEndPort());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::constructionPlaceIntermediatePointAtSanePositions()
{
  DrawPort startPort(Point(10,20));
  DrawPort endPort(Point(30,40));
  Connection *connection = ConnectionFactory::produceConstruction(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), connection->getPoints()[0]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), connection->getPoints()[1]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,40), connection->getPoints()[2]->getAbsolutePosition());

  ConnectionFactory::dispose(connection);
}


void ConnectionFactoryTest::connectionIsRegisteredAtStartPort()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(1), startPort.ports.size());
  CPPUNIT_ASSERT(startPort.ports.find(connection->getPoints().front()) != startPort.ports.end());
  CPPUNIT_ASSERT(endPort.ports.find(connection->getPoints().front()) == endPort.ports.end());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::connectionIsRegisteredAtEndPort()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(1), endPort.ports.size());
  CPPUNIT_ASSERT(startPort.ports.find(connection->getPoints().back()) == startPort.ports.end());
  CPPUNIT_ASSERT(endPort.ports.find(connection->getPoints().back()) != endPort.ports.end());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::dispose_removes_connection_from_ports()
{
  SimplePort startPort;
  SimplePort endPort;

  Connection *connection = ConnectionFactory::produce(&startPort, &endPort);
  ConnectionFactory::dispose(connection);

  CPPUNIT_ASSERT_EQUAL(size_t(0), startPort.ports.size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), endPort.ports.size());
}

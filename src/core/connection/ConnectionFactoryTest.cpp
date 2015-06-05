#include "ConnectionFactoryTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"
#include "SimplePort.hpp"

#include "../util/contract.hpp"

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

void ConnectionFactoryTest::createInvalidConnection()
{
  SimplePort startPort;
  SimplePort endPort;
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce(&startPort, &endPort, {1, 2, 3}), PreconditionError);
}

void ConnectionFactoryTest::createConnection()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractPort*>(&startPort), connection->getStartPort());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractPort*>(&endPort), connection->getEndPort());
  //TODO reimplement
//  CPPUNIT_ASSERT(startPort.ports.find(connection->getPoints().front()) != startPort.ports.end());
//  CPPUNIT_ASSERT(endPort.ports.find(connection->getPoints().back()) != endPort.ports.end());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createPathConnection()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {-10, 3, -5, 4, 1, -2, 7});

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
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractPort*>(&startPort), connection->getStartPort());
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<AbstractPort*>(&endPort), connection->getEndPort());

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

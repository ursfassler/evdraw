#include "ConnectionFactoryTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"

#include "../util/contract.hpp"

void ConnectionFactoryTest::cleanup()
{
  Connection connection;
  ConnectionFactory::cleanup(connection);
}

void ConnectionFactoryTest::canNotDisposeNullptr()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::dispose(nullptr), PreconditionError);
}

void ConnectionFactoryTest::createEmptyConnection()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce({}), PreconditionError);
}

void ConnectionFactoryTest::createInvalidConnection()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce({1, 2, 3, 4, 5, 6}), PreconditionError);
}

void ConnectionFactoryTest::createConnection()
{
  Connection *connection = ConnectionFactory::produce(-10, 0, 10, 0);

  CPPUNIT_ASSERT_EQUAL(PortPoint(Point(-10,0)), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint(Point( 10,0)), connection->getEnd());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createDiagonalConnection()
{
  Connection *connection = ConnectionFactory::produce(-10, -5, 10, 5);

  CPPUNIT_ASSERT_EQUAL(PortPoint(Point(-10,-5)), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint(Point( 10, 5)), connection->getEnd());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point( 0,-5), connection->getIntermediatePoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 0, 5), connection->getIntermediatePoints()[1]->getPosition());

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(0, connection->getVerticalSegment()[0]->getX());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getHorizontalSegment()[0]->getY());
  CPPUNIT_ASSERT_EQUAL( 5, connection->getHorizontalSegment()[1]->getY());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createPathConnection()
{
  Connection *connection = ConnectionFactory::produce({-10, 3, -5, 4, 1, -2, 7});

  CPPUNIT_ASSERT_EQUAL(PortPoint(Point(-10,  3)), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint(Point(  7, -2)), connection->getEnd());

  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(-5, 3), connection->getIntermediatePoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(-5, 4), connection->getIntermediatePoints()[1]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 1, 4), connection->getIntermediatePoints()[2]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 1,-2), connection->getIntermediatePoints()[3]->getPosition());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getVerticalSegment()[0]->getX());
  CPPUNIT_ASSERT_EQUAL( 1, connection->getVerticalSegment()[1]->getX());

  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL( 3, connection->getHorizontalSegment()[0]->getY());
  CPPUNIT_ASSERT_EQUAL( 4, connection->getHorizontalSegment()[1]->getY());
  CPPUNIT_ASSERT_EQUAL(-2, connection->getHorizontalSegment()[2]->getY());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createBuildToEnd()
{
  PartialConnectionFromStart *connection = ConnectionFactory::producePartialFromStart();

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection->getStart().getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection->getEnd().getPosition());

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&connection->getStart()), connection->getHorizontalSegment()[0]->getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection->getIntermediatePoints()[0]), connection->getHorizontalSegment()[0]->getEnd());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection->getIntermediatePoints()[0]), connection->getVerticalSegment()[0]->getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&connection->getEnd()), connection->getVerticalSegment()[0]->getEnd());

  ConnectionFactory::dispose(connection);
}


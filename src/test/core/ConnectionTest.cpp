#include "ConnectionTest.hpp"

#include <core/Connection.hpp>
#include <core/ConnectionFactory.hpp>
#include <core/Segment.hpp>

void ConnectionTest::createEmptyConnection()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce({}), std::invalid_argument);
}

void ConnectionTest::createInvalidConnection()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce({1, 2, 3, 4, 5, 6}), std::invalid_argument);
}

void ConnectionTest::createConnection()
{
  Connection *connection = ConnectionFactory::produce(-10, 0, 10, 0);

  CPPUNIT_ASSERT_EQUAL(PortPoint(-10,0), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint( 10,0), connection->getEnd());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());

  ConnectionFactory::dispose(connection);
}

void ConnectionTest::createDiagonalConnection()
{
  Connection *connection = ConnectionFactory::produce(-10, -5, 10, 5);

  CPPUNIT_ASSERT_EQUAL(PortPoint(-10,-5), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint( 10, 5), connection->getEnd());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL( 0, connection->getIntermediatePoints()[0]->getX());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getIntermediatePoints()[0]->getY());
  CPPUNIT_ASSERT_EQUAL( 0, connection->getIntermediatePoints()[1]->getX());
  CPPUNIT_ASSERT_EQUAL( 5, connection->getIntermediatePoints()[1]->getY());

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(0, connection->getVerticalSegment()[0]->getX());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getHorizontalSegment()[0]->getY());
  CPPUNIT_ASSERT_EQUAL( 5, connection->getHorizontalSegment()[1]->getY());

  ConnectionFactory::dispose(connection);
}

void ConnectionTest::createPathConnection()
{
  Connection *connection = ConnectionFactory::produce({-10, 3, -5, 4, 1, -2, 7});

  CPPUNIT_ASSERT_EQUAL(PortPoint(-10,  3), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint(  7, -2), connection->getEnd());

  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getIntermediatePoints()[0]->getX());
  CPPUNIT_ASSERT_EQUAL( 3, connection->getIntermediatePoints()[0]->getY());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getIntermediatePoints()[1]->getX());
  CPPUNIT_ASSERT_EQUAL( 4, connection->getIntermediatePoints()[1]->getY());
  CPPUNIT_ASSERT_EQUAL( 1, connection->getIntermediatePoints()[2]->getX());
  CPPUNIT_ASSERT_EQUAL( 4, connection->getIntermediatePoints()[2]->getY());
  CPPUNIT_ASSERT_EQUAL( 1, connection->getIntermediatePoints()[3]->getX());
  CPPUNIT_ASSERT_EQUAL(-2, connection->getIntermediatePoints()[3]->getY());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getVerticalSegment()[0]->getX());
  CPPUNIT_ASSERT_EQUAL( 1, connection->getVerticalSegment()[1]->getX());

  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL( 3, connection->getHorizontalSegment()[0]->getY());
  CPPUNIT_ASSERT_EQUAL( 4, connection->getHorizontalSegment()[1]->getY());
  CPPUNIT_ASSERT_EQUAL(-2, connection->getHorizontalSegment()[2]->getY());

  ConnectionFactory::dispose(connection);
}

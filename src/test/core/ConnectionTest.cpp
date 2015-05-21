#include "ConnectionTest.hpp"

#include <core/Connection.hpp>
#include <core/ConnectionFactory.hpp>
#include <core/Segment.hpp>

void ConnectionTest::createEmptyConnection()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::create({}), std::invalid_argument);
}

void ConnectionTest::createInvalidConnection()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::create({1, 2, 3, 4, 5, 6}), std::invalid_argument);
}

void ConnectionTest::createConnection()
{
  Connection *connection = ConnectionFactory::create(-10, 0, 10, 0);

  CPPUNIT_ASSERT_EQUAL(PortPoint(-10,0), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint( 10,0), connection->getEnd());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());

  delete connection;
}

void ConnectionTest::createDiagonalConnection()
{
  Connection *connection = ConnectionFactory::create(-10, -5, 10, 5);

  CPPUNIT_ASSERT_EQUAL(PortPoint(-10,-5), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint( 10, 5), connection->getEnd());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(IntermediatePoint(0,-5), connection->getIntermediatePoints()[0]);
  CPPUNIT_ASSERT_EQUAL(IntermediatePoint(0, 5), connection->getIntermediatePoints()[1]);

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(0, connection->getVerticalSegment()[0].getX());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getHorizontalSegment()[0].getY());
  CPPUNIT_ASSERT_EQUAL( 5, connection->getHorizontalSegment()[1].getY());

  delete connection;
}

void ConnectionTest::createPathConnection()
{
  Connection *connection = ConnectionFactory::create({-10, 3, -5, 4, 1, -2, 7});

  CPPUNIT_ASSERT_EQUAL(PortPoint(-10,  3), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint(  7, -2), connection->getEnd());

  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(IntermediatePoint(-5, 3), connection->getIntermediatePoints()[0]);
  CPPUNIT_ASSERT_EQUAL(IntermediatePoint(-5, 4), connection->getIntermediatePoints()[1]);
  CPPUNIT_ASSERT_EQUAL(IntermediatePoint( 1, 4), connection->getIntermediatePoints()[2]);
  CPPUNIT_ASSERT_EQUAL(IntermediatePoint( 1,-2), connection->getIntermediatePoints()[3]);

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getVerticalSegment()[0].getX());
  CPPUNIT_ASSERT_EQUAL( 1, connection->getVerticalSegment()[1].getX());

  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL( 3, connection->getHorizontalSegment()[0].getY());
  CPPUNIT_ASSERT_EQUAL( 4, connection->getHorizontalSegment()[1].getY());
  CPPUNIT_ASSERT_EQUAL(-2, connection->getHorizontalSegment()[2].getY());

  delete connection;
}

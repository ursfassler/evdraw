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
  CPPUNIT_ASSERT_THROW(ConnectionFactory::create({1, 2, 3, 4}), std::invalid_argument);
}

void ConnectionTest::createConnection()
{
  const std::vector<PaperUnit> path = {-10, 0, 10};
  Connection *connection = ConnectionFactory::create(path);

  CPPUNIT_ASSERT_EQUAL(PortPoint(-10,0), connection->getStart());
  CPPUNIT_ASSERT_EQUAL(PortPoint( 10,0), connection->getEnd());

  delete connection;
}

void ConnectionTest::segmentsForSimpleConnection()
{
  const std::vector<PaperUnit> path = {-10, 3, 10};
  Connection *connection = ConnectionFactory::create(path);

  CPPUNIT_ASSERT_EQUAL(size_t(0), connection->getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(3, connection->getHorizontalSegment()[0].getY());

  delete connection;
}

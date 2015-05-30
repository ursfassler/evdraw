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
  std::vector<PaperUnit> empty;
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce(empty), PreconditionError);
}

void ConnectionFactoryTest::createInvalidConnection()
{
  CPPUNIT_ASSERT_THROW(ConnectionFactory::produce({1, 2, 3, 4, 5, 6}), PreconditionError);
}

void ConnectionFactoryTest::createConnection()
{
  Connection *connection = ConnectionFactory::produce(-10, 0, 10, 0);

  CPPUNIT_ASSERT_EQUAL(Point(-10,0), connection->getStart()->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 10,0), connection->getEnd()->getPosition());
  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(connection->getStart(), connection->getPoints()[0]);
  CPPUNIT_ASSERT_EQUAL(connection->getEnd(), connection->getPoints()[3]);
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createDiagonalConnection()
{
  Connection *connection = ConnectionFactory::produce(-10, -5, 10, 5);

  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(-10,-5), connection->getPoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 0,-5), connection->getPoints()[1]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 0, 5), connection->getPoints()[2]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 10, 5), connection->getPoints()[3]->getPosition());

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

  CPPUNIT_ASSERT_EQUAL(size_t(6), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(-10, 3), connection->getPoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( -5, 3), connection->getPoints()[1]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( -5, 4), connection->getPoints()[2]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(  1, 4), connection->getPoints()[3]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(  1,-2), connection->getPoints()[4]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(  7,-2), connection->getPoints()[5]->getPosition());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(-5, connection->getVerticalSegment()[0]->getX());
  CPPUNIT_ASSERT_EQUAL( 1, connection->getVerticalSegment()[1]->getX());

  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL( 3, connection->getHorizontalSegment()[0]->getY());
  CPPUNIT_ASSERT_EQUAL( 4, connection->getHorizontalSegment()[1]->getY());
  CPPUNIT_ASSERT_EQUAL(-2, connection->getHorizontalSegment()[2]->getY());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createConstructionConnection()
{
  ConstructionConnection *connection = ConnectionFactory::produceConstructionConnection();

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection->getRoot()->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection->getLeaf()->getPosition());

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection->getPoints()[0]), connection->getHorizontalSegment()[0]->getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection->getPoints()[1]), connection->getHorizontalSegment()[0]->getEnd());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection->getPoints()[1]), connection->getVerticalSegment()[0]->getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection->getPoints()[2]), connection->getVerticalSegment()[0]->getEnd());

  ConnectionFactory::dispose(connection);
}

void ConnectionFactoryTest::createConnectionFromConstruction()
{
  ConstructionConnection *cc = ConnectionFactory::produceConstructionConnection();
  cc->getLeaf()->setPosition(Point(10,20));

  CPPUNIT_ASSERT_EQUAL(Point( 0, 0), cc->getPoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10, 0), cc->getPoints()[1]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), cc->getPoints()[2]->getPosition());

  Connection *con = ConnectionFactory::produce(*cc);

  CPPUNIT_ASSERT_EQUAL(size_t(4),    con->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point( 0, 0), con->getPoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10, 0), con->getPoints()[1]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), con->getPoints()[2]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), con->getPoints()[3]->getPosition());

  ConnectionFactory::dispose(cc);
  ConnectionFactory::dispose(con);
}

void ConnectionFactoryTest::createLongerConnectionFromConstruction()
{
  ConstructionConnection *cc = ConnectionFactory::produceConstructionConnection();
  cc->getLeaf()->setPosition(Point(10,20));
  cc->addSegment();
  cc->getLeaf()->setPosition(Point(15,20));

  CPPUNIT_ASSERT_EQUAL(Point( 0, 0), cc->getPoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10, 0), cc->getPoints()[1]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), cc->getPoints()[2]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(15,20), cc->getPoints()[3]->getPosition());

  Connection *con = ConnectionFactory::produce(*cc);

  CPPUNIT_ASSERT_EQUAL(size_t(4),    con->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point( 0, 0), con->getPoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10, 0), con->getPoints()[1]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), con->getPoints()[2]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(15,20), con->getPoints()[3]->getPosition());

  ConnectionFactory::dispose(cc);
  ConnectionFactory::dispose(con);
}

#include "ConnectionTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"

#include "../util/contract.hpp"

void ConnectionTest::createFinished()
{
  ConnectionBase connection;
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getStart().getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getEnd().getPosition());
}

void ConnectionTest::createBuild()
{
  ConnectionBase connection;
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getStart().getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getEnd().getPosition());
}


void ConnectionTest::addHorizontalSegment()
{
  ConnectionBase connection;
  HorizontalSegment *segment = new HorizontalSegment(&connection.getStart(), &connection.getEnd());

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getHorizontalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addVerticalSegment()
{
  ConnectionBase connection;
  VerticalSegment *segment = new VerticalSegment(&connection.getStart(), &connection.getEnd());

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getVerticalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addIntermediatePoint()
{
  ConnectionBase connection;
  IntermediatePoint *ip = new IntermediatePoint(Point(0,0));

  connection.addIntermediatePoint(ip);
  CPPUNIT_ASSERT_EQUAL(ip, connection.getIntermediatePoints()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::buildToEndAndAddSegment()
{
  PartialConnectionFromStart *connection = ConnectionFactory::producePartialFromStart();

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getIntermediatePoints().size());

  connection->addSegment();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());

  connection->addSegment();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getIntermediatePoints().size());

  ConnectionFactory::dispose(connection);
}

void ConnectionTest::buildToEndAndFinish()
{
  PartialConnectionFromStart *connection = ConnectionFactory::producePartialFromStart();
  connection->buildFinished();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());

  ConnectionFactory::dispose(connection);
}

void ConnectionTest::buildToEndAddAndFinish()
{
  PartialConnectionFromStart *connection = ConnectionFactory::producePartialFromStart();
  connection->addSegment();
  connection->buildFinished();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getIntermediatePoints().size());

  ConnectionFactory::dispose(connection);
}

class ConnectionObserverTest : public ConnectionObserver
{
  public:
    virtual void addVerticalSegment(const ConnectionBase *parent, VerticalSegment *segment)
    {
      lastParent = parent;
      lastAddVerticalSegment = segment;
    }

    virtual void addHorizontalSegment(const ConnectionBase *parent, HorizontalSegment *segment)
    {
      lastParent = parent;
      lastAddHorizontalSegment = segment;
    }

    ConnectionBase const * lastParent = nullptr;
    VerticalSegment *lastAddVerticalSegment = nullptr;
    HorizontalSegment *lastAddHorizontalSegment = nullptr;
};

void ConnectionTest::notifyWhenAddVerticalSegment()
{
  ConnectionBase connection;
  ConnectionObserverTest observer;
  connection.registerObserver(&observer);
  VerticalSegment *segment = new VerticalSegment(&connection.getStart(), &connection.getEnd());

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(static_cast<const ConnectionBase*>(&connection), observer.lastParent);
  CPPUNIT_ASSERT_EQUAL(segment, observer.lastAddVerticalSegment);

  connection.unregisterObserver(&observer);
  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::notifyWhenAddHorizontalSegment()
{
  ConnectionBase connection;
  ConnectionObserverTest observer;
  connection.registerObserver(&observer);
  HorizontalSegment *segment = new HorizontalSegment(&connection.getStart(), &connection.getEnd());

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(static_cast<const ConnectionBase*>(&connection), observer.lastParent);
  CPPUNIT_ASSERT_EQUAL(segment, observer.lastAddHorizontalSegment);

  connection.unregisterObserver(&observer);
  ConnectionFactory::cleanup(connection);
}


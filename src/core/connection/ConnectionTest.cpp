#include "ConnectionTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"

#include "../util/contract.hpp"

void ConnectionTest::create()
{
  Connection connection;
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getPoints().size());
}

void ConnectionTest::addHorizontalSegment()
{
  Connection connection;
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  HorizontalSegment *segment = new HorizontalSegment(&a, &b);

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getHorizontalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addVerticalSegment()
{
  Connection connection;
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  VerticalSegment *segment = new VerticalSegment(&a, &b);

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getVerticalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addPoint()
{
  Connection connection;
  Endpoint *ip = new IntermediatePoint(Point(0,0));

  connection.addPoint(ip);
  CPPUNIT_ASSERT_EQUAL(ip, connection.getPoints()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::constructAndInsertSegment()
{
  Connection *connection = ConnectionFactory::produceConstructionConnection(Point(0,0));

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getPoints().size());
  Endpoint *firstPoint = connection->getPoints()[0];
  Endpoint *secondPoint = connection->getPoints()[1];
  Endpoint *lastPoint = connection->getPoints().back();

  connection->insertSegmentAtEnd();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(firstPoint, connection->getPoints()[0]);
  CPPUNIT_ASSERT_EQUAL(secondPoint, connection->getPoints()[1]);
  CPPUNIT_ASSERT_EQUAL(lastPoint, connection->getPoints().back());
  CPPUNIT_ASSERT_EQUAL(lastPoint, connection->getEnd());
  Endpoint *thirdPoint = connection->getPoints()[2];

  connection->insertSegmentAtEnd();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(5), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(firstPoint, connection->getPoints()[0]);
  CPPUNIT_ASSERT_EQUAL(secondPoint, connection->getPoints()[1]);
  CPPUNIT_ASSERT_EQUAL(thirdPoint, connection->getPoints()[2]);
  CPPUNIT_ASSERT_EQUAL(lastPoint, connection->getPoints().back());
  CPPUNIT_ASSERT_EQUAL(lastPoint, connection->getEnd());

  ConnectionFactory::dispose(connection);
}

class ConnectionObserverTest : public ConnectionObserver
{
  public:
    virtual void addVerticalSegment(const Connection *parent, VerticalSegment *segment)
    {
      lastParent = parent;
      lastAddVerticalSegment = segment;
    }

    virtual void addHorizontalSegment(const Connection *parent, HorizontalSegment *segment)
    {
      lastParent = parent;
      lastAddHorizontalSegment = segment;
    }

    Connection const * lastParent = nullptr;
    VerticalSegment *lastAddVerticalSegment = nullptr;
    HorizontalSegment *lastAddHorizontalSegment = nullptr;
};

void ConnectionTest::notifyWhenAddVerticalSegment()
{
  Connection connection;
  ConnectionObserverTest observer;
  connection.registerObserver(&observer);
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  VerticalSegment *segment = new VerticalSegment(&a,&b);

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Connection*>(&connection), observer.lastParent);
  CPPUNIT_ASSERT_EQUAL(segment, observer.lastAddVerticalSegment);

  connection.unregisterObserver(&observer);
  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::notifyWhenAddHorizontalSegment()
{
  Connection connection;
  ConnectionObserverTest observer;
  connection.registerObserver(&observer);
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  HorizontalSegment *segment = new HorizontalSegment(&a,&b);

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Connection*>(&connection), observer.lastParent);
  CPPUNIT_ASSERT_EQUAL(segment, observer.lastAddHorizontalSegment);

  connection.unregisterObserver(&observer);
  ConnectionFactory::cleanup(connection);
}


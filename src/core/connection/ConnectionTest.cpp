#include "ConnectionTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"

#include "../util/contract.hpp"

void ConnectionTest::create()
{
  ConnectionBase connection;
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getPoints().size());
}

void ConnectionTest::addHorizontalSegment()
{
  ConnectionBase connection;
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  HorizontalSegment *segment = new HorizontalSegment(&a, &b);

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getHorizontalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addVerticalSegment()
{
  ConnectionBase connection;
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  VerticalSegment *segment = new VerticalSegment(&a, &b);

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getVerticalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addPoint()
{
  ConnectionBase connection;
  Endpoint *ip = new IntermediatePoint(Point(0,0));

  connection.addPoint(ip);
  CPPUNIT_ASSERT_EQUAL(ip, connection.getPoints()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::buildToEndAndAddSegment()
{
  ConstructionConnection *connection = ConnectionFactory::produceConstructionConnection();

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getPoints().size());

  connection->addSegment();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getPoints().size());

  connection->addSegment();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(5), connection->getPoints().size());

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
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  VerticalSegment *segment = new VerticalSegment(&a,&b);

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
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  HorizontalSegment *segment = new HorizontalSegment(&a,&b);

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(static_cast<const ConnectionBase*>(&connection), observer.lastParent);
  CPPUNIT_ASSERT_EQUAL(segment, observer.lastAddHorizontalSegment);

  connection.unregisterObserver(&observer);
  ConnectionFactory::cleanup(connection);
}


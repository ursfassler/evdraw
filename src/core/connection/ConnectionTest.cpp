#include "ConnectionTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"
#include "SimplePort.hpp"

#include "../instance/AbstractInstance.hpp"
#include "../util/contract.hpp"

class Instance : public AbstractInstance
{
  public:
    Instance(const std::string &aName) :
      name(aName)
    {
    }

    const std::string &getName() const
    {
      return name;
    }

    const AbstractPort *findPort(const std::string &) const
    {
      return nullptr;
    }

  private:
    std::string name;
};

void ConnectionTest::create()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getPoints().size());
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractPort*>(&startPort), connection.getStartPort());
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractPort*>(&endPort), connection.getEndPort());
}

void ConnectionTest::instanceStart()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);

  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getPoints().size());
}

void ConnectionTest::addHorizontalSegment()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  HorizontalSegment *segment = new HorizontalSegment(&a, &b);

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getHorizontalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addVerticalSegment()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);
  PortPoint a(Point(0,0));
  PortPoint b(Point(0,0));
  VerticalSegment *segment = new VerticalSegment(&a, &b);

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getVerticalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addPoint()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);
  Endpoint *ip = new IntermediatePoint(Point(0,0));

  connection.addPoint(ip);
  CPPUNIT_ASSERT_EQUAL(ip, connection.getPoints()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::constructAndInsertSegment()
{
  SimplePort a;
  SimplePort b;
  Connection *connection = ConnectionFactory::produceConstruction(&a, &b);

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
  Endpoint *thirdPoint = connection->getPoints()[2];

  connection->insertSegmentAtEnd();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection->getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(5), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(firstPoint, connection->getPoints()[0]);
  CPPUNIT_ASSERT_EQUAL(secondPoint, connection->getPoints()[1]);
  CPPUNIT_ASSERT_EQUAL(thirdPoint, connection->getPoints()[2]);
  CPPUNIT_ASSERT_EQUAL(lastPoint, connection->getPoints().back());

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
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);
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
  SimplePort startPort;
  SimplePort endPort;
  Connection connection(&startPort, &endPort);
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


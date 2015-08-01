#include "ConnectionTest.hpp"

#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/connection/Segment.hpp>
#include <core/connection/SimplePort.hpp>
#include <core/connection/DrawPort.hpp>

#include <core/instance/AbstractInstance.hpp>
#include <core/util/contract.hpp>

class Instance : public AbstractInstance
{
  public:
    Instance(const std::string &aName) :
      AbstractInstance(Point(0,0)),
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
  Endpoint a(Point(0,0));
  Endpoint b(Point(0,0));
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
  Endpoint a(Point(0,0));
  Endpoint b(Point(0,0));
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
  Endpoint *ip = new Endpoint(Point(0,0));

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

void ConnectionTest::insertSegmentAtSanePosition()
{
  DrawPort a(Point(10,20));
  DrawPort b(Point(30,50));
  Connection *connection = ConnectionFactory::produceConstruction(&a, &b);

  CPPUNIT_ASSERT_EQUAL(size_t(3), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), connection->getPoints()[0]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), connection->getPoints()[1]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,50), connection->getPoints()[2]->getAbsolutePosition());

  connection->insertSegmentAtEnd();

  CPPUNIT_ASSERT_EQUAL(size_t(4), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), connection->getPoints()[0]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), connection->getPoints()[1]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,50), connection->getPoints()[2]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,50), connection->getPoints()[3]->getAbsolutePosition());

  connection->insertSegmentAtEnd();

  CPPUNIT_ASSERT_EQUAL(size_t(5), connection->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(10,20), connection->getPoints()[0]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), connection->getPoints()[1]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,50), connection->getPoints()[2]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,50), connection->getPoints()[3]->getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,50), connection->getPoints()[4]->getAbsolutePosition());

  ConnectionFactory::dispose(connection);
}

class ConnectionObserverTest : public ConnectionObserver
{
  public:
    virtual void verticalSegmentAdded(VerticalSegment *segment)
    {
      lastAddVerticalSegment = segment;
    }

    virtual void horizontalSegmentAdded(HorizontalSegment *segment)
    {
      lastAddHorizontalSegment = segment;
    }

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
  Endpoint a(Point(0,0));
  Endpoint b(Point(0,0));
  VerticalSegment *segment = new VerticalSegment(&a,&b);

  connection.addVerticalSegment(segment);
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
  Endpoint a(Point(0,0));
  Endpoint b(Point(0,0));
  HorizontalSegment *segment = new HorizontalSegment(&a,&b);

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, observer.lastAddHorizontalSegment);

  connection.unregisterObserver(&observer);
  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::replaceStartPort()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort);

  SimplePort startPort2;

  CPPUNIT_ASSERT_EQUAL(size_t(1), startPort.ports.size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), startPort2.ports.size());
  connection->replaceStartPort(&startPort2);
  CPPUNIT_ASSERT_EQUAL(size_t(0), startPort.ports.size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), startPort2.ports.size());

  ConnectionFactory::dispose(connection);
}

void ConnectionTest::replaceEndPort()
{
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort);

  SimplePort endPort2;

  CPPUNIT_ASSERT_EQUAL(size_t(1), endPort.ports.size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), endPort2.ports.size());
  connection->replaceEndPort(&endPort2);
  CPPUNIT_ASSERT_EQUAL(size_t(0), endPort.ports.size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), endPort2.ports.size());

  ConnectionFactory::dispose(connection);
}

void ConnectionTest::pathMinimal()
{
  DrawPort a(Point(10,15));
  DrawPort b(Point(30,50));
  Connection *connection = ConnectionFactory::produce(&a, &b);

  CPPUNIT_ASSERT_EQUAL(std::vector<PaperUnit>({20}), connection->getPath());

  ConnectionFactory::dispose(connection);
}

void ConnectionTest::pathLong()
{
  DrawPort a(Point(10,15));
  DrawPort b(Point(30,50));
  Connection *connection = ConnectionFactory::produce(&a, &b, {-3, 11, 75, 4, 2});

  CPPUNIT_ASSERT_EQUAL(std::vector<PaperUnit>({-3, 11, 75, 4, 2}), connection->getPath());

  ConnectionFactory::dispose(connection);
}

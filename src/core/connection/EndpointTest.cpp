#include "EndpointTest.hpp"


void EndpointTest::initialPortPointPosition()
{
  PortPoint point(1, 2);
  CPPUNIT_ASSERT_EQUAL(1, point.getX());
  CPPUNIT_ASSERT_EQUAL(2, point.getY());
}

void EndpointTest::portPointIsFixed()
{
  PortPoint point(0, 0);
  CPPUNIT_ASSERT_EQUAL(false, point.freeMovable());
}

void EndpointTest::initialIntermediatePointPosition()
{
  IntermediatePoint point(1, 2);
  CPPUNIT_ASSERT_EQUAL(1, point.getX());
  CPPUNIT_ASSERT_EQUAL(2, point.getY());
}

void EndpointTest::intermediatePointIsMovable()
{
  IntermediatePoint point(0, 0);
  CPPUNIT_ASSERT_EQUAL(true, point.freeMovable());
}

void EndpointTest::setXpos()
{
  IntermediatePoint point(0, 0);

  point.setX(42);

  CPPUNIT_ASSERT_EQUAL(42, point.getX());
  CPPUNIT_ASSERT_EQUAL( 0, point.getY());
}

void EndpointTest::setYpos()
{
  IntermediatePoint point(0, 0);

  point.setY(42);

  CPPUNIT_ASSERT_EQUAL( 0, point.getX());
  CPPUNIT_ASSERT_EQUAL(42, point.getY());
}

class EpObserver : public Observer<Endpoint>
{
  public:
    void notify(const Endpoint *sender)
    {
      lastSender = sender;
    }

    Endpoint const *lastSender = nullptr;
};

void EndpointTest::notifyListenerX()
{
  IntermediatePoint ep(0, 0);
  EpObserver observer;

  ep.registerObserver(&observer);

  ep.setX(42);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Endpoint*>(&ep), observer.lastSender);

  ep.unregisterObserver(&observer);
}

void EndpointTest::notifyListenerY()
{
  IntermediatePoint ep(0, 0);
  EpObserver observer;

  ep.registerObserver(&observer);

  ep.setY(42);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Endpoint*>(&ep), observer.lastSender);

  ep.unregisterObserver(&observer);
}

#include "EndpointTest.hpp"


void EndpointTest::initialPortPointPosition()
{
  PortPoint point(Point(1, 2));
  CPPUNIT_ASSERT_EQUAL(Point(1,2), point.getPosition());
}

void EndpointTest::portPointIsFixed()
{
  PortPoint point(Point(0, 0));
  CPPUNIT_ASSERT_EQUAL(false, point.freeMovable());
}

void EndpointTest::initialIntermediatePointPosition()
{
  IntermediatePoint point(Point(1, 2));
  CPPUNIT_ASSERT_EQUAL(Point(1,2), point.getPosition());
}

void EndpointTest::intermediatePointIsMovable()
{
  IntermediatePoint point(Point(0, 0));
  CPPUNIT_ASSERT_EQUAL(true, point.freeMovable());
}

void EndpointTest::setPosition()
{
  IntermediatePoint point(Point(0, 0));

  point.setPosition(Point(42,57));

  CPPUNIT_ASSERT_EQUAL(Point(42,57), point.getPosition());
}

class EpObserver : public EndpointObserver
{
  public:
    void positionChanged(const Endpoint *sender)
    {
      lastSender = sender;
    }

    Endpoint const *lastSender = nullptr;
};

void EndpointTest::notifyListenerOnPosChange()
{
  IntermediatePoint ep(Point(0, 0));
  EpObserver observer;

  ep.registerObserver(&observer);

  ep.setPosition(Point(42,57));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Endpoint*>(&ep), observer.lastSender);

  ep.unregisterObserver(&observer);
}

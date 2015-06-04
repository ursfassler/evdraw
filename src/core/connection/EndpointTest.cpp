#include "EndpointTest.hpp"


void EndpointTest::inheritsFromPositionable()
{
  Endpoint pp(Point(1, 2));

  CPPUNIT_ASSERT(dynamic_cast<RelativePosition*>(&pp) != nullptr);
}

void EndpointTest::isMovableWhenNotHaveAnchor()
{
  Endpoint pp(Point(1, 2));
  CPPUNIT_ASSERT(pp.freeMovable());
}

void EndpointTest::isNotMovableWhenHaveAnchor()
{
  RelativePosition p(Point(0,0));
  Endpoint pp(Point(1, 2));
  pp.replaceAnchor(&p);
  CPPUNIT_ASSERT(!pp.freeMovable());
}

void EndpointTest::initialPortPointPosition()
{
  Endpoint point(Point(1, 2));
  CPPUNIT_ASSERT_EQUAL(Point(1,2), point.getOffset());
}

void EndpointTest::setPosition()
{
  Endpoint point(Point(0, 0));

  point.setOffset(Point(42,57));

  CPPUNIT_ASSERT_EQUAL(Point(42,57), point.getOffset());
}

class EpObserver : public PositionObserver
{
  public:
    void absolutePositionChanged(const RelativePosition *sender)
    {
      lastSender = sender;
    }

    void offsetChanged(const RelativePosition *)
    {
    }

    RelativePosition const *lastSender = nullptr;
};

void EndpointTest::notifyListenerOnPosChange()
{
  Endpoint ep(Point(0, 0));
  EpObserver observer;

  ep.registerObserver(&observer);

  ep.setOffset(Point(42,57));
  CPPUNIT_ASSERT_EQUAL(dynamic_cast<const RelativePosition*>(&ep), observer.lastSender);

  ep.unregisterObserver(&observer);
}

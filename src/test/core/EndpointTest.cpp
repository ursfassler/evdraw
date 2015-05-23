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

class Listener : public EndpointListener
{
  public:
    void changeX(const Endpoint *sender)
    {
      lastChangeXSender = sender;
    }

    void changeY(const Endpoint *sender)
    {
      lastChangeYSender = sender;
    }

    Endpoint const *lastChangeXSender = nullptr;
    Endpoint const *lastChangeYSender = nullptr;
};

void EndpointTest::addRemoveListener()
{
  IntermediatePoint ep(0, 0);
  Listener listener;

  CPPUNIT_ASSERT_EQUAL(false, ep.hasListener());
  ep.addListener(&listener);
  CPPUNIT_ASSERT_EQUAL(true, ep.hasListener());
  ep.removeListener(&listener);
  CPPUNIT_ASSERT_EQUAL(false, ep.hasListener());
}

void EndpointTest::notifyListenerX()
{
  IntermediatePoint ep(0, 0);
  Listener listener;

  ep.addListener(&listener);

  ep.setX(42);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Endpoint*>(&ep), listener.lastChangeXSender);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Endpoint*>(nullptr), listener.lastChangeYSender);
}

void EndpointTest::notifyListenerY()
{
  IntermediatePoint ep(0, 0);
  Listener listener;

  ep.addListener(&listener);

  ep.setY(42);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Endpoint*>(nullptr), listener.lastChangeXSender);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Endpoint*>(&ep), listener.lastChangeYSender);
}

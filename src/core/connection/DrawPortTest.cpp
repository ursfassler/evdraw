#include "DrawPortTest.hpp"

#include "DrawPort.hpp"
#include "AbstractPort.hpp"
#include "../base/Position.hpp"

class Observer : public PositionObserver
{
  public:
    void absolutePositionChanged(const RelativePosition *sender)
    {
      absolutePositionSender = sender;
    }

    void offsetChanged(const RelativePosition *sender)
    {
      offsetSender = sender;
    }

    RelativePosition const * absolutePositionSender = nullptr;
    RelativePosition const * offsetSender = nullptr;
};

void DrawPortTest::inheritsAbstractPort()
{
  DrawPort port(Point(0,0));
  CPPUNIT_ASSERT(dynamic_cast<AbstractPort*>(&port) != nullptr);
}

void DrawPortTest::inheritsPosition()
{
  DrawPort port(Point(0,0));
  CPPUNIT_ASSERT(dynamic_cast<Position*>(&port) != nullptr);
}

void DrawPortTest::getAnchorPosition()
{
  DrawPort port(Point(10,20));
  RelativePosition point(Point(0,0));
  port.addConnectionPoint(&point);

  CPPUNIT_ASSERT_EQUAL(Point(10,20), point.getAbsolutePosition());

  port.removeConnectionPoint(&point);
}

void DrawPortTest::getInformedByPositionChange()
{
  DrawPort port(Point(0,0));
  RelativePosition point(Point(0,0));
  port.addConnectionPoint(&point);
  Observer observer;
  port.registerObserver(&observer);
  port.setAbsolutePosition(Point(10,20));

  CPPUNIT_ASSERT(observer.absolutePositionSender != nullptr);

  port.unregisterObserver(&observer);
  port.removeConnectionPoint(&point);
}

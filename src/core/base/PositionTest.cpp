#include "PositionTest.hpp"

#include "Position.hpp"

#include "../types.hpp"

void PositionTest::create()
{
  RelativePosition base(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(10,20), base.getOffset());
}

void PositionTest::absolutePosition()
{
  RelativePosition parent(Point(20,60));
  RelativePosition base(Point(10,20));
  base.replaceAnchor(&parent);
  CPPUNIT_ASSERT_EQUAL(Point(30,80), base.getAbsolutePosition());
}

void PositionTest::setOffset()
{
  RelativePosition base(Point(0,0));
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(10,20), base.getOffset());
}

void PositionTest::setAbsolutePosition()
{
  RelativePosition parent(Point(10,20));
  RelativePosition base(Point(0,0));
  base.replaceAnchor(&parent);

  base.setAbsolutePosition(Point(15,30));

  CPPUNIT_ASSERT_EQUAL(Point(10,20), parent.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(5,10), base.getOffset());
}

class TestBaseObserver : public PositionObserver
{
  public:
    virtual void absolutePositionChanged(const RelativePosition *subject)
    {
      lastPositionChanger = subject;
    }

    virtual void offsetChanged(const RelativePosition *subject)
    {
      lastOffsetChanger = subject;
    }

    RelativePosition const * lastPositionChanger = nullptr;
    RelativePosition const * lastOffsetChanger = nullptr;
};

void PositionTest::notifyOnChange()
{
  RelativePosition base(Point(0,0));
  TestBaseObserver observer;
  base.registerObserver(&observer);

  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(&base), observer.lastOffsetChanger);
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(&base), observer.lastPositionChanger);

  base.unregisterObserver(&observer);
}

void PositionTest::notifyChildOnChange()
{
  RelativePosition base(Point(0,0));
  RelativePosition baseChild(Point(0,0));
  baseChild.replaceAnchor(&base);

  TestBaseObserver observer;
  baseChild.registerObserver(&observer);

  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(nullptr), observer.lastOffsetChanger);
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(&baseChild), observer.lastPositionChanger);

  baseChild.unregisterObserver(&observer);
}

void PositionTest::notifyGrandchildOnChange()
{
  RelativePosition base(Point(0,0));
  RelativePosition baseChild(Point(0,0));
  baseChild.replaceAnchor(&base);
  RelativePosition baseGrandchild(Point(0,0));
  baseGrandchild.replaceAnchor(&baseChild);

  TestBaseObserver observer;
  baseGrandchild.registerObserver(&observer);

  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(nullptr), observer.lastOffsetChanger);
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(&baseGrandchild), observer.lastPositionChanger);

  baseGrandchild.unregisterObserver(&observer);
}

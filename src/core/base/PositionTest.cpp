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

class TestBaseObserver : public PositionObserver
{
  public:
    virtual void notify(const RelativePosition *subject)
    {
      lastSubject = subject;
    }

    RelativePosition const * lastSubject = nullptr;
};

void PositionTest::notifyOnChange()
{
  RelativePosition base(Point(0,0));
  TestBaseObserver observer;
  base.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(&base), observer.lastSubject);

  base.unregisterObserver(&observer);
}

void PositionTest::notifyChildOnChange()
{
  RelativePosition base(Point(0,0));
  RelativePosition baseChild(Point(0,0));
  baseChild.replaceAnchor(&base);

  TestBaseObserver observer;
  baseChild.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(&baseChild), observer.lastSubject);

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

  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const RelativePosition*>(&baseGrandchild), observer.lastSubject);

  baseGrandchild.unregisterObserver(&observer);
}

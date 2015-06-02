#include "BaseTest.hpp"

#include "Base.hpp"

#include "../types.hpp"

void BaseTest::create()
{
  Positionable base(nullptr, Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(10,20), base.getOffset());
}

void BaseTest::absolutePosition()
{
  Positionable parent(nullptr, Point(20,60));
  Positionable base(&parent, Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(30,80), base.getAbsolutePosition());
}

void BaseTest::setOffset()
{
  Positionable base(nullptr, Point(0,0));
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(10,20), base.getOffset());
}

class TestBaseObserver : public PositionableObserver
{
  public:
    virtual void notify(const Positionable *subject)
    {
      lastSubject = subject;
    }

    Positionable const * lastSubject = nullptr;
};

void BaseTest::notifyOnChange()
{
  Positionable base(nullptr, Point(0,0));
  TestBaseObserver observer;
  base.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Positionable*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Positionable*>(&base), observer.lastSubject);

  base.unregisterObserver(&observer);
}

void BaseTest::notifyChildOnChange()
{
  Positionable base(nullptr, Point(0,0));
  Positionable baseChild(&base, Point(0,0));

  TestBaseObserver observer;
  baseChild.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Positionable*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Positionable*>(&baseChild), observer.lastSubject);

  baseChild.unregisterObserver(&observer);
}

void BaseTest::notifyGrandchildOnChange()
{
  Positionable base(nullptr, Point(0,0));
  Positionable baseChild(&base, Point(0,0));
  Positionable baseGrandchild(&baseChild, Point(0,0));

  TestBaseObserver observer;
  baseGrandchild.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Positionable*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Positionable*>(&baseGrandchild), observer.lastSubject);

  baseGrandchild.unregisterObserver(&observer);
}

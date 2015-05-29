#include "BaseTest.hpp"

#include "Base.hpp"

#include "../types.hpp"

void BaseTest::create()
{
  Base base(nullptr, Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(10,20), base.getOffset());
}

void BaseTest::absolutePosition()
{
  Base parent(nullptr, Point(20,60));
  Base base(&parent, Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(30,80), base.getAbsolutePosition());
}

void BaseTest::setOffset()
{
  Base base(nullptr, Point(0,0));
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(Point(10,20), base.getOffset());
}

class TestBaseObserver : public BaseObserver
{
  public:
    virtual void notify(const Base *subject)
    {
      lastSubject = subject;
    }

    Base const * lastSubject = nullptr;
};

void BaseTest::notifyOnChange()
{
  Base base(nullptr, Point(0,0));
  TestBaseObserver observer;
  base.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Base*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Base*>(&base), observer.lastSubject);

  base.unregisterObserver(&observer);
}

void BaseTest::notifyChildOnChange()
{
  Base base(nullptr, Point(0,0));
  Base baseChild(&base, Point(0,0));

  TestBaseObserver observer;
  baseChild.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Base*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Base*>(&baseChild), observer.lastSubject);

  baseChild.unregisterObserver(&observer);
}

void BaseTest::notifyGrandchildOnChange()
{
  Base base(nullptr, Point(0,0));
  Base baseChild(&base, Point(0,0));
  Base baseGrandchild(&baseChild, Point(0,0));

  TestBaseObserver observer;
  baseGrandchild.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Base*>(nullptr), observer.lastSubject);
  base.setOffset(Point(10,20));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Base*>(&baseGrandchild), observer.lastSubject);

  baseGrandchild.unregisterObserver(&observer);
}

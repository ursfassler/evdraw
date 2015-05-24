#include "InstanceTest.hpp"

#include "../component/Component.hpp"
#include "../base/Base.hpp"
#include "../Point.hpp"
#include "Instance.hpp"

void InstanceTest::produce()
{
  Component component;
  Instance  instance(Point(3, 7), &component);

  CPPUNIT_ASSERT_EQUAL(Point(3, 7), instance.getOffset());
  CPPUNIT_ASSERT_EQUAL(&component, instance.getComponent());
}

void InstanceTest::setPosition()
{
  Component component;
  Instance  instance(Point(0, 0), &component);

  CPPUNIT_ASSERT_EQUAL(Point( 0,  0), instance.getOffset());
  instance.setOffset(Point(57, 42));
  CPPUNIT_ASSERT_EQUAL(Point(57, 42), instance.getOffset());
}

class EpObserver : public Observer<Instance>
{
  public:
    Instance const *lastSender = nullptr;

  public:
    void notify(const Instance *sender)
    {
      lastSender = sender;
    }
};

void InstanceTest::inheritsBase()
{
  Component component;
  Instance  instance(Point(0, 0), &component);
  CPPUNIT_ASSERT(dynamic_cast<Base*>(&instance) != nullptr);
}

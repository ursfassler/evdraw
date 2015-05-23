#include "InstanceTest.hpp"

#include "../component/Component.hpp"
#include "../types.hpp"
#include "Instance.hpp"

void InstanceTest::produce()
{
  Component component;
  Instance  instance(Point(3, 7), &component);

  CPPUNIT_ASSERT_EQUAL(Point(3, 7), instance.getPosition());
  CPPUNIT_ASSERT_EQUAL(&component, instance.getComponent());
}

void InstanceTest::setPosition()
{
  Component component;
  Instance  instance(Point(0, 0), &component);

  CPPUNIT_ASSERT_EQUAL(Point( 0,  0), instance.getPosition());
  instance.setPosition(Point(57, 42));
  CPPUNIT_ASSERT_EQUAL(Point(57, 42), instance.getPosition());
}

class EpListener : public InstanceListener
{
  public:
    Instance const *lastSender = nullptr;

  public:
    void positionChange(const Instance *sender)
    {
      lastSender = sender;
    }
};

void InstanceTest::positionChanged()
{
  Component component;
  Instance  instance(Point(0, 0), &component);

  EpListener listener;
  instance.addListener(&listener);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Instance*>(nullptr), listener.lastSender);
  instance.setPosition(Point(57, 42));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Instance*>(&instance), listener.lastSender);

  instance.removeListener(&listener);
}

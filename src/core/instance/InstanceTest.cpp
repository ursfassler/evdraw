#include "InstanceTest.hpp"

#include "../component/Component.hpp"
#include "../component/ComponentFactory.hpp"
#include "../base/Base.hpp"
#include "../Point.hpp"
#include "Instance.hpp"
#include "InstancePort.hpp"
#include "InstanceFactory.hpp"
#include "AbstractInstance.hpp"

void InstanceTest::produce()
{
  Component component("");
  Instance  instance("lala", Point(3, 7), &component);

  CPPUNIT_ASSERT_EQUAL(std::string("lala"), instance.getName());
  CPPUNIT_ASSERT_EQUAL(Point(3, 7), instance.getOffset());
  CPPUNIT_ASSERT_EQUAL(&component, instance.getComponent());
  CPPUNIT_ASSERT(dynamic_cast<AbstractInstance*>(&instance) != nullptr);
}

void InstanceTest::setPosition()
{
  Component component("");
  Instance  instance("", Point(0, 0), &component);

  CPPUNIT_ASSERT_EQUAL(Point( 0,  0), instance.getOffset());
  instance.setOffset(Point(57, 42));
  CPPUNIT_ASSERT_EQUAL(Point(57, 42), instance.getOffset());
}

class EpObserver
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
  Component component("");
  Instance  instance("", Point(0, 0), &component);
  CPPUNIT_ASSERT(dynamic_cast<Positionable*>(&instance) != nullptr);
}

void InstanceTest::addInputPort()
{
  Instance  instance("", Point(0, 0), nullptr);

  InstancePort *port = new InstancePort(&instance, nullptr, Point(-20,10));
  instance.addPort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(1), instance.getPorts().size());
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractPort*>(port), instance.getPorts()[0]);

  InstanceFactory::cleanup(instance);
}


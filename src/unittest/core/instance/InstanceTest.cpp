#include "InstanceTest.hpp"

#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/base/Position.hpp>
#include <core/Point.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/instance/AbstractInstance.hpp>

void InstanceTest::produce()
{
  Component *component = ComponentFactory::produce("");
  Instance  instance("lala", Point(3, 7), component);

  CPPUNIT_ASSERT_EQUAL(std::string("lala"), instance.getName());
  CPPUNIT_ASSERT_EQUAL(Point(3, 7), instance.getOffset());
  CPPUNIT_ASSERT_EQUAL(component, instance.getComponent());
  CPPUNIT_ASSERT(dynamic_cast<AbstractInstance*>(&instance) != nullptr);

  ComponentFactory::dispose(component);
}

void InstanceTest::setPosition()
{
  Component *component = ComponentFactory::produce("");
  Instance  instance("", Point(0, 0), component);

  CPPUNIT_ASSERT_EQUAL(Point( 0,  0), instance.getOffset());
  instance.setOffset(Point(57, 42));
  CPPUNIT_ASSERT_EQUAL(Point(57, 42), instance.getOffset());

  ComponentFactory::dispose(component);
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

void InstanceTest::inheritsPosition()
{
  Component *component = ComponentFactory::produce("");
  Instance  instance("", Point(0, 0), component);
  CPPUNIT_ASSERT(dynamic_cast<Position*>(&instance) != nullptr);

  ComponentFactory::dispose(component);
}

void InstanceTest::inheritsBase()
{
  Component *component = ComponentFactory::produce("");
  Instance  instance("", Point(0, 0), component);
  CPPUNIT_ASSERT(dynamic_cast<Base*>(&instance) != nullptr);

  ComponentFactory::dispose(component);
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

void InstanceTest::getPortWithExisting()
{
  Component *component = ComponentFactory::produce("", {"in1", "in2"}, {"out1"});
  Instance  *instance = InstanceFactory::produce(component, "", Point(0,0));

  AbstractPort *in2 = instance->getPort("in2");
  AbstractPort *out1 = instance->getPort("out1");
  AbstractPort *in1 = instance->getPort("in1");

  CPPUNIT_ASSERT(in1 != nullptr);
  CPPUNIT_ASSERT(in2 != nullptr);
  CPPUNIT_ASSERT(out1 != nullptr);

  CPPUNIT_ASSERT(in1 != in2);
  CPPUNIT_ASSERT(in1 != out1);
  CPPUNIT_ASSERT(in2 != out1);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}


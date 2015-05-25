#include "InstanceFactoryTest.hpp"

#include "InstanceFactory.hpp"
#include "Instance.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentFactory.hpp"


void InstanceFactoryTest::componentCanNotBeNullptr()
{
  CPPUNIT_ASSERT_THROW(InstanceFactory::produce(nullptr, "", Point(0,0)), PreconditionError);
}

void InstanceFactoryTest::canNotDisposeNullptr()
{
  CPPUNIT_ASSERT_THROW(InstanceFactory::dispose(nullptr), PreconditionError);
}

void InstanceFactoryTest::cleanupRemovesInput()
{
  Instance instance("", Point(0,0), nullptr);
  instance.addInput(new InstancePort(nullptr, nullptr, Point(0,0)));
  InstanceFactory::cleanup(instance);
  CPPUNIT_ASSERT(instance.getInput().empty());
}

void InstanceFactoryTest::cleanupRemovesOutput()
{
  Instance instance("", Point(0,0), nullptr);
  instance.addOutput(new InstancePort(nullptr, nullptr, Point(0,0)));
  InstanceFactory::cleanup(instance);
  CPPUNIT_ASSERT(instance.getOutput().empty());
}

void InstanceFactoryTest::produceSimple()
{
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  CPPUNIT_ASSERT_EQUAL(component, instance->getComponent());
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), instance->getName());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), instance->getAbsolutePosition());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void InstanceFactoryTest::produceWithPorts()
{
  Component *component = ComponentFactory::produce("Component", {"in1", "in2", "in3"}, {"out1", "out2"});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getInput().size());
  CPPUNIT_ASSERT_EQUAL(component->getPortLeft()[0], instance->getInput()[0]->getCompPort());
  CPPUNIT_ASSERT_EQUAL(component->getPortLeft()[1], instance->getInput()[1]->getCompPort());
  CPPUNIT_ASSERT_EQUAL(component->getPortLeft()[2], instance->getInput()[2]->getCompPort());

  CPPUNIT_ASSERT_EQUAL(size_t(2), instance->getOutput().size());
  CPPUNIT_ASSERT_EQUAL(component->getPortRight()[0], instance->getOutput()[0]->getCompPort());
  CPPUNIT_ASSERT_EQUAL(component->getPortRight()[1], instance->getOutput()[1]->getCompPort());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

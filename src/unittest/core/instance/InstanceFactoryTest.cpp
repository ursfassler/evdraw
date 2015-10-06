// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceFactoryTest.hpp"

#include <core/instance/InstanceFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/component/InstanceAppearance.hpp>
#include <core/implementation/NullImplementation.hpp>

#include <functional>

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
  Component *component = ComponentFactory::produce("Component", {"in"}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  InstanceFactory::cleanup(*instance);
  CPPUNIT_ASSERT(instance->getPorts().empty());
  delete instance;

  ComponentFactory::dispose(component);
}

void InstanceFactoryTest::produceSimple()
{
  Component *component = ComponentFactory::produce("Component");
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

  CPPUNIT_ASSERT_EQUAL(component, instance->getComponent());
  CPPUNIT_ASSERT_EQUAL(size_t(5), instance->getPorts().size());
  CPPUNIT_ASSERT( dynamic_cast<InstancePort*>(instance->getPorts()[0]) != nullptr);

  auto ip = [instance](int i)
  {
    return dynamic_cast<InstancePort*>(instance->getPorts()[i]);
  };

  IInstance *ainst = instance;
  CPPUNIT_ASSERT(ainst != nullptr);
  CPPUNIT_ASSERT_EQUAL(ainst, ip(0)->getInstance());
  CPPUNIT_ASSERT_EQUAL(ainst, ip(1)->getInstance());
  CPPUNIT_ASSERT_EQUAL(ainst, ip(2)->getInstance());
  CPPUNIT_ASSERT_EQUAL(ainst, ip(3)->getInstance());
  CPPUNIT_ASSERT_EQUAL(ainst, ip(4)->getInstance());

  std::set<std::string> names;
  for (auto i = 0; i < 5; i++ ) {
    names.insert(ip(i)->getName());
  }
  CPPUNIT_ASSERT(names.find("in1") != names.end());
  CPPUNIT_ASSERT(names.find("in2") != names.end());
  CPPUNIT_ASSERT(names.find("in3") != names.end());
  CPPUNIT_ASSERT(names.find("out1") != names.end());
  CPPUNIT_ASSERT(names.find("out2") != names.end());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void InstanceFactoryTest::rightConnectorIsAtCorrectPosition()
{
  Component *component = ComponentFactory::produce("", {}, {""});
  Instance *instance = InstanceFactory::produce(component, "", Point(0,0));

  InstancePort *port = dynamic_cast<InstancePort*>(instance->getPorts()[0]);
  CPPUNIT_ASSERT(port != nullptr);
  CPPUNIT_ASSERT_EQUAL(InstanceAppearance::connectorOffset(), port->getConnector().getAbsolutePosition().x);
  CPPUNIT_ASSERT_EQUAL(InstanceAppearance::portVerticalOffset(0), port->getConnector().getAbsolutePosition().y);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void InstanceFactoryTest::leftConnectorIsAtCorrectPosition()
{
  Component *component = ComponentFactory::produce("", {""}, {});
  Instance *instance = InstanceFactory::produce(component, "", Point(0,0));

  InstancePort *port = dynamic_cast<InstancePort*>(instance->getPorts()[0]);
  CPPUNIT_ASSERT(port != nullptr);
  CPPUNIT_ASSERT_EQUAL(-InstanceAppearance::connectorOffset(), port->getConnector().getAbsolutePosition().x);
  CPPUNIT_ASSERT_EQUAL(InstanceAppearance::portVerticalOffset(0), port->getConnector().getAbsolutePosition().y);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

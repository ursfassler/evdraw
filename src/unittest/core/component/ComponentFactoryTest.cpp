// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentFactoryTest.hpp"

#include <core/component/ComponentFactory.hpp>
#include <core/component/Component.hpp>
#include <core/implementation/NullImplementation.hpp>
#include <core/util/contract.hpp>

#include <string>

void ComponentFactoryTest::produceSimple()
{
  Component *component = ComponentFactory::produce("Component");

  CPPUNIT_ASSERT_EQUAL(std::string("Component"), component->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), component->getPorts().size());

  ComponentFactory::dispose(component);
}

void ComponentFactoryTest::produce()
{
  Component *component = ComponentFactory::produce("Component", {"in1", "in2", "in3"}, {"out1", "out2"});

  CPPUNIT_ASSERT_EQUAL(std::string("Component"), component->getName());

  CPPUNIT_ASSERT_EQUAL(size_t(5),           component->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"),  component->getPorts()[0]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0),           component->getPorts()[0]->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(std::string("in2"),  component->getPorts()[1]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(1),           component->getPorts()[1]->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(std::string("in3"),  component->getPorts()[2]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(2),           component->getPorts()[2]->getTopIndex());

  CPPUNIT_ASSERT_EQUAL(std::string("out1"), component->getPorts()[3]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0),           component->getPorts()[3]->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(std::string("out2"), component->getPorts()[4]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(1),           component->getPorts()[4]->getTopIndex());

  ComponentFactory::dispose(component);
}

void ComponentFactoryTest::canNotDisposeNullptr()
{
  CPPUNIT_ASSERT_THROW(ComponentFactory::dispose(nullptr), PreconditionError);
}

void ComponentFactoryTest::cleanupComponentOnStack()
{
  Component component("", new NullImplementation());
  ComponentPort *port = new ComponentPort("", PortType::Slot);
  component.addPort(port);

  ComponentFactory::cleanup(component);
}

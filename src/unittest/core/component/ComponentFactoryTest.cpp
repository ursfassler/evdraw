#include "ComponentFactoryTest.hpp"

#include <core/component/ComponentFactory.hpp>
#include <core/component/Component.hpp>
#include <core/util/contract.hpp>

#include <string>

void ComponentFactoryTest::produce()
{
  Component *component = ComponentFactory::produce("Component", {"in1", "in2", "in3"}, {"out1", "out2"});

  CPPUNIT_ASSERT_EQUAL(std::string("Component"), component->getName());

  CPPUNIT_ASSERT_EQUAL(size_t(3),           component->getPortLeft().size());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"),  component->getPortLeft()[0]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0),           component->getPortLeft()[0]->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(std::string("in2"),  component->getPortLeft()[1]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(1),           component->getPortLeft()[1]->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(std::string("in3"),  component->getPortLeft()[2]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(2),           component->getPortLeft()[2]->getTopIndex());

  CPPUNIT_ASSERT_EQUAL(size_t(2),           component->getPortRight().size());
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), component->getPortRight()[0]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0),           component->getPortRight()[0]->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(std::string("out2"), component->getPortRight()[1]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(1),           component->getPortRight()[1]->getTopIndex());

  ComponentFactory::dispose(component);
}

void ComponentFactoryTest::canNotDisposeNullptr()
{
  CPPUNIT_ASSERT_THROW(ComponentFactory::dispose(nullptr), PreconditionError);
}

void ComponentFactoryTest::cleanupComponentOnStack()
{
  Component component("");
  ComponentPort *port = new ComponentPort("");
  component.addPortLeft(port);

  ComponentFactory::cleanup(component);
}

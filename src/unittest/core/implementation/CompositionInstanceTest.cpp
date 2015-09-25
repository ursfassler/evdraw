#include "CompositionInstanceTest.hpp"
#include "../component/ComponentMock.hpp"

#include <core/implementation/CompositionInstance.hpp>
#include <core/component/ComponentFactory.hpp>

void CompositionInstanceTest::create()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  CPPUNIT_ASSERT_EQUAL(static_cast<IComponent*>(&component), testee.getComponent());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getWidth());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getHeight());
  CPPUNIT_ASSERT_EQUAL(size_t(0), testee.getPorts().size());
}

void CompositionInstanceTest::can_change_width()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  testee.setWidth(1234);

  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getHeight());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(1234), testee.getWidth());
}

void CompositionInstanceTest::can_change_height()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  testee.setHeight(1234);

  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getWidth());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(1234), testee.getHeight());
}

void CompositionInstanceTest::create_from_component_with_ports()
{
  Component *component = ComponentFactory::produce("", {"in1", "in2"}, {"out"});
  CompositionInstance *testee = new CompositionInstance(component);

  CPPUNIT_ASSERT_EQUAL(size_t(3), testee->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"), testee->getPorts()[0]->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("in2"), testee->getPorts()[1]->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("out"), testee->getPorts()[2]->getName());

  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(testee), testee->getPorts()[0]->getInstance());
  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(testee), testee->getPorts()[1]->getInstance());
  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(testee), testee->getPorts()[2]->getInstance());

  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::syncs_with_new_ports_in_composition()
{
  Component *component = ComponentFactory::produce("", {}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component->addPort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(1), testee->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(port, testee->getPorts()[0]->getCompPort());

  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::syncs_with_deleted_ports_in_composition()
{
  Component *component = ComponentFactory::produce("", {""}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  ComponentPort *port = component->getPorts()[0];
  component->deletePort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(0), testee->getPorts().size());

  delete testee;
  ComponentFactory::dispose(component);
}

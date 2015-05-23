#include "ComponentTest.hpp"

#include <core/Component.hpp>
#include <core/ComponentPort.hpp>

void ComponentTest::produce()
{
  Component comp;
}

void ComponentTest::addPortLeft()
{
  Component     comp;
  ComponentPort *port = new ComponentPort("left1");

  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.getPortLeft().size());
  comp.addPortLeft(port);
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp.getPortLeft().size());
  CPPUNIT_ASSERT_EQUAL(port, comp.getPortLeft()[0]);
}

void ComponentTest::addPortRight()
{
  Component     comp;
  ComponentPort *port = new ComponentPort("right1");

  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.getPortRight().size());
  comp.addPortRight(port);
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp.getPortRight().size());
  CPPUNIT_ASSERT_EQUAL(port, comp.getPortRight()[0]);
}

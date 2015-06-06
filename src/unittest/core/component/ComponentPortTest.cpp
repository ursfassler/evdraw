#include "ComponentPortTest.hpp"

#include <core/component/ComponentPort.hpp>

#include <string>

void ComponentPortTest::produce()
{
  ComponentPort port("hallo");

  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port.getTopIndex());
}

void ComponentPortTest::setTopIndex()
{
  ComponentPort port("hallo");
  port.setTopIndex(42);
  CPPUNIT_ASSERT_EQUAL(size_t(42), port.getTopIndex());
}

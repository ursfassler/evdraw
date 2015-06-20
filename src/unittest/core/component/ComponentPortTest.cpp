#include "ComponentPortTest.hpp"

#include <core/component/ComponentPort.hpp>

#include <string>

void ComponentPortTest::setTopIndex()
{
  Signal port("hallo");
  port.setTopIndex(42);
  CPPUNIT_ASSERT_EQUAL(size_t(42), port.getTopIndex());
}


void SignalTest::produce()
{
  Signal port("hallo");

  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port.getTopIndex());
}


void SlotTest::produce()
{
  Slot port("hallo");

  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port.getTopIndex());
}

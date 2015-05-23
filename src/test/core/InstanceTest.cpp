#include "InstanceTest.hpp"

#include <core/Component.hpp>
#include <core/Instance.hpp>

void InstanceTest::produce()
{
  Component component;
  Instance  instance(3, 7, &component);

  CPPUNIT_ASSERT_EQUAL(3, instance.getX());
  CPPUNIT_ASSERT_EQUAL(7, instance.getY());
  CPPUNIT_ASSERT_EQUAL(&component, instance.getComponent());
}


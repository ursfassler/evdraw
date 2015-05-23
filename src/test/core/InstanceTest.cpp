#include "InstanceTest.hpp"

#include <core/Component.hpp>
#include <core/Instance.hpp>

void InstanceTest::produce()
{
  Component component;
  Instance  instance(&component);

  CPPUNIT_ASSERT_EQUAL(&component, instance.getComponent());
}


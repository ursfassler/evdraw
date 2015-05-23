#include "ComponentPortTest.hpp"

#include "ComponentPort.hpp"

#include <string>

void ComponentPortTest::produce()
{
  ComponentPort port("hallo");

  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
}

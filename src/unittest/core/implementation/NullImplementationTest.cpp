#include "NullImplementationTest.hpp"

#include <core/implementation/NullImplementation.hpp>


void NullImplementationTest::construct()
{
  NullImplementation  implementation;
  (void)(implementation);
}

void NullImplementationTest::inheritsAbstractImplementation()
{
  NullImplementation  implementation;
  CPPUNIT_ASSERT(dynamic_cast<AbstractImplementation*>(&implementation) != nullptr);
}

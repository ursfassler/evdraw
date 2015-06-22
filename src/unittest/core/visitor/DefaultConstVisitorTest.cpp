#include "DefaultConstVisitorTest.hpp"

#include <core/visitor/ConstVisitor.hpp>
#include <core/visitor/DefaultConstVisitor.hpp>

void DefaultConstVisitorTest::implementsVisitor()
{
  DefaultConstVisitor defaultVisitor;
  ConstVisitor *visitor = dynamic_cast<ConstVisitor*>(&defaultVisitor);
  CPPUNIT_ASSERT(visitor != nullptr);
}

void DefaultConstVisitorTest::implementsAllVisitMethods()
{
  DefaultConstVisitor defaultVisitor;
}

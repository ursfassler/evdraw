#include "NullConstVisitorTest.hpp"

#include <core/visitor/ConstVisitor.hpp>
#include <core/visitor/NullConstVisitor.hpp>

void NullConstVisitorTest::implementsVisitor()
{
  NullConstVisitor defaultVisitor;
  ConstVisitor *visitor = dynamic_cast<ConstVisitor*>(&defaultVisitor);
  CPPUNIT_ASSERT(visitor != nullptr);
}

void NullConstVisitorTest::implementsAllVisitMethods()
{
  NullConstVisitor defaultVisitor;
}

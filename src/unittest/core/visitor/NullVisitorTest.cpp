#include "NullVisitorTest.hpp"

#include <core/visitor/Visitor.hpp>
#include <core/visitor/NullVisitor.hpp>

void NullVisitorTest::implementsVisitor()
{
  NullVisitor defaultVisitor;
  Visitor *visitor = dynamic_cast<Visitor*>(&defaultVisitor);
  CPPUNIT_ASSERT(visitor != nullptr);
}

void NullVisitorTest::implementsAllVisitMethods()
{
  NullVisitor defaultVisitor;
}

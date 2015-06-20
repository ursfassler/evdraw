#include "DefaultVisitorTest.hpp"

#include <core/visitor/Visitor.hpp>
#include <core/visitor/DefaultVisitor.hpp>

void DefaultVisitorTest::implementsVisitor()
{
  DefaultVisitor defaultVisitor;
  Visitor *visitor = dynamic_cast<Visitor*>(&defaultVisitor);
  CPPUNIT_ASSERT(visitor != nullptr);
}

void DefaultVisitorTest::implementsAllVisitMethods()
{
  DefaultVisitor defaultVisitor;
}

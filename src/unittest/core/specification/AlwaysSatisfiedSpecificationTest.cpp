#include "AlwaysSatisfiedSpecificationTest.hpp"

#include <core/specification/AlwaysSatisfiedSpecification.hpp>
#include <core/specification/Specification.hpp>

void AlwaysSatisfiedSpecificationTest::inheritsSpecification()
{
  AlwaysSatisfiedSpecification spec;
  CPPUNIT_ASSERT(dynamic_cast<Specification*>(&spec) != nullptr);
}

void AlwaysSatisfiedSpecificationTest::satisfiedOnNullptr()
{
  AlwaysSatisfiedSpecification spec;
  CPPUNIT_ASSERT(spec.isSatisfiedBy(nullptr));
}
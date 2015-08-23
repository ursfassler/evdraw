// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

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

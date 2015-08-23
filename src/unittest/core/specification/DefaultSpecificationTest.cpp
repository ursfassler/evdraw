// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "DefaultSpecificationTest.hpp"

#include <core/specification/DefaultSpecification.hpp>
#include <core/specification/Specification.hpp>
#include <core/specification/OrSpecification.hpp>

class TestDefaultSpecificationTest : public DefaultSpecification
{
  public:
    bool isSatisfiedBy(const Base *) const
    {
      return false;
    }
};

void DefaultSpecificationTest::inheritsSpecification()
{
  TestDefaultSpecificationTest spec;
  CPPUNIT_ASSERT(dynamic_cast<Specification*>(&spec) != nullptr);
}

void DefaultSpecificationTest::orReturnsOrSpecification()
{
  Specification *left = new TestDefaultSpecificationTest();
  Specification *right = new TestDefaultSpecificationTest();
  Specification *ored = left->or_(right);

  CPPUNIT_ASSERT(dynamic_cast<OrSpecification*>(ored) != nullptr);
  CPPUNIT_ASSERT(left != ored);
  CPPUNIT_ASSERT(right != ored);

  delete ored;
}

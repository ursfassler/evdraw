#include "DefaultSpecificationTest.hpp"

#include <core/util/DefaultSpecification.hpp>
#include <core/util/Specification.hpp>
#include <core/util/OrSpecification.hpp>

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

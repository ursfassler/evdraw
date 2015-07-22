#include <core/base/Base.hpp>
#include <core/util/Specification.hpp>

#include "SpecificationTest.hpp"

class TestSpecification : public Specification
{
  public:
    TestSpecification(bool &aDestructorCalled) :
      destructorCalled(aDestructorCalled)
    {
    }

    ~TestSpecification()
    {
      destructorCalled = true;
    }

    bool isSatisfiedBy(const Base *candidate) const
    {
      return candidate != nullptr;
    }

    Specification *or_(const Specification *) const
    {
      return new TestSpecification(destructorCalled);
    }

  private:
    bool &destructorCalled;

};

void SpecificationTest::destructorIsVirtual()
{
  bool destructed = false;
  Specification *test = new TestSpecification(destructed);
  delete test;

  CPPUNIT_ASSERT(destructed);
}

void SpecificationTest::hasVirtualIsSatisfiedBy()
{
  bool destructed = false;
  Specification *test = new TestSpecification(destructed);
  Base base;

  CPPUNIT_ASSERT(test->isSatisfiedBy(&base));
  CPPUNIT_ASSERT(!test->isSatisfiedBy(nullptr));

  delete test;
}

void SpecificationTest::hasVirtualOr()
{
  bool destructed = false;
  Specification *test = new TestSpecification(destructed);

  Specification *ored = test->or_(test);
  CPPUNIT_ASSERT(test != ored);

  delete ored;
  delete test;
}

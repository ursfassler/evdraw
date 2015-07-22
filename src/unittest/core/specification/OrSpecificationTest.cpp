#include "OrSpecificationTest.hpp"

#include <core/specification/OrSpecification.hpp>
#include <core/specification/DefaultSpecification.hpp>

class TestOrSpecFalse : public DefaultSpecification
{
  public:
    bool isSatisfiedBy(const Base *) const
    {
      return false;
    }
};

class TestOrSpecTrue : public DefaultSpecification
{
  public:
    bool isSatisfiedBy(const Base *) const
    {
      return true;
    }
};

class TestOrSpecificationDestructor : public DefaultSpecification
{
  public:
    TestOrSpecificationDestructor(int &aDestructorCalled) :
      destructorCalled(aDestructorCalled)
    {
    }

    ~TestOrSpecificationDestructor()
    {
      destructorCalled++;
    }

    bool isSatisfiedBy(const Base *candidate) const
    {
      return candidate != nullptr;
    }

  private:
    int &destructorCalled;
};

void OrSpecificationTest::inheritsSpecification()
{
  OrSpecification spec;
  CPPUNIT_ASSERT(dynamic_cast<Specification*>(&spec) != nullptr);
}

void OrSpecificationTest::noOredReturnFalse()
{
  OrSpecification spec;
  CPPUNIT_ASSERT(!spec.isSatisfiedBy(nullptr));
}

void OrSpecificationTest::addSpecTakesOwnership()
{
  int destroyed = 0;
  OrSpecification *spec = new OrSpecification();
  spec->add(new TestOrSpecificationDestructor(destroyed));
  delete spec;

  CPPUNIT_ASSERT_EQUAL(1, destroyed);
}

void OrSpecificationTest::addTrueReturnsTrue()
{
  OrSpecification spec;
  spec.add(new TestOrSpecTrue());
  CPPUNIT_ASSERT(spec.isSatisfiedBy(nullptr));
}

void OrSpecificationTest::addFalseReturnFalse()
{
  OrSpecification spec;
  spec.add(new TestOrSpecFalse());
  CPPUNIT_ASSERT(!spec.isSatisfiedBy(nullptr));
}

void OrSpecificationTest::addFalseTrueReturnsTrue()
{
  OrSpecification spec;
  spec.add(new TestOrSpecFalse());
  spec.add(new TestOrSpecTrue());
  CPPUNIT_ASSERT(spec.isSatisfiedBy(nullptr));
}

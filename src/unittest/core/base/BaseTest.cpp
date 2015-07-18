#include "BaseTest.hpp"

#include <core/base/Base.hpp>

class TestBase : public Base
{
  public:
    TestBase(bool &aDestructorCalled) :
      destructorCalled(aDestructorCalled)
    {
    }

    ~TestBase()
    {
      destructorCalled = true;
    }

  private:
    bool &destructorCalled;

};

void BaseTest::destructorIsVirtual()
{
  bool destructed = false;
  Base *test = new TestBase(destructed);
  delete test;

  CPPUNIT_ASSERT(destructed);
}

#include "AbstractImplementationTest.hpp"

#include <core/component/AbstractImplementation.hpp>

class Implementation : public AbstractImplementation
{
  public:
    Implementation(bool &aDestructorCalled) :
      destructorCalled(aDestructorCalled)
    {
    }

    ~Implementation()
    {
      destructorCalled = true;
    }

    bool &destructorCalled;
};

void AbstractImplementationTest::construct()
{
  AbstractImplementation  implementation;
  (void)(implementation);
}

void AbstractImplementationTest::destructorIsVirtual()
{
  bool destructorCalled = false;
  AbstractImplementation *impl = new Implementation(destructorCalled);
  delete impl;
  CPPUNIT_ASSERT(destructorCalled);
}

void AbstractImplementationTest::constructNullImplementation()
{
  NullImplementation  implementation;
  (void)(implementation);
}

void AbstractImplementationTest::nullImplementationInheritsAbstractImplementation()
{
  NullImplementation  implementation;
  CPPUNIT_ASSERT(dynamic_cast<AbstractImplementation*>(&implementation) != nullptr);
}

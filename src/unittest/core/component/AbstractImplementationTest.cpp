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

    void accept(Visitor &) const
    {
    }

    bool &destructorCalled;
};

void AbstractImplementationTest::destructorIsVirtual()
{
  bool destructorCalled = false;
  AbstractImplementation *impl = new Implementation(destructorCalled);
  delete impl;
  CPPUNIT_ASSERT(destructorCalled);
}

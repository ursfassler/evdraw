// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "AbstractImplementationTest.hpp"

#include <core/component/IImplementation.hpp>

class Implementation : public IImplementation
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

    void accept(Visitor &)
    {
    }

    void accept(ConstVisitor &) const
    {
    }

    bool &destructorCalled;
};

void AbstractImplementationTest::destructorIsVirtual()
{
  bool destructorCalled = false;
  IImplementation *impl = new Implementation(destructorCalled);
  delete impl;
  CPPUNIT_ASSERT(destructorCalled);
}

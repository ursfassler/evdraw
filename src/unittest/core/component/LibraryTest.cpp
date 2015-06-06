#include "LibraryTest.hpp"

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>

void LibraryTest::create()
{
  Library lib;
}

void LibraryTest::addComponent()
{
  Component *comp = new Component("comp");
  Library lib;
  lib.add(comp);
  CPPUNIT_ASSERT(lib.contains(comp));
}

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

void LibraryTest::deletsComponentsWhenDeleted()
{
  Library *lib = new Library();
  bool deleted = false;
  Implementation *impl = new Implementation(deleted);
  Component *comp = new Component("comp", impl);
  lib->add(comp);
  delete lib;

  CPPUNIT_ASSERT(deleted);
}


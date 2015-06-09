#include "LibraryTest.hpp"

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>

void LibraryTest::create()
{
  Library lib;
  CPPUNIT_ASSERT_EQUAL(size_t(0), lib.getComponents().size());
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

void LibraryTest::getComponent()
{
  Component *comp = new Component("comp");
  Library lib;
  lib.add(comp);

  Component *ret = lib.getComponent("comp");
  CPPUNIT_ASSERT_EQUAL(comp, ret);
}

void LibraryTest::getCorrectComponent()
{
  Component *comp = new Component("comp3");
  Library lib;
  lib.add(new Component("comp1"));
  lib.add(new Component("comp2"));
  lib.add(comp);
  lib.add(new Component("comp4"));
  lib.add(new Component("comp5"));
  lib.add(new Component("comp6"));

  Component *ret = lib.getComponent("comp3");
  CPPUNIT_ASSERT_EQUAL(comp, ret);
}

void LibraryTest::throwErrorWhenComponentNotInLibrary()
{
  Library lib;
  CPPUNIT_ASSERT_THROW(lib.getComponent("lala"), std::invalid_argument);
}


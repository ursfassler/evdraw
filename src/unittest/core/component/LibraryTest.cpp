#include "LibraryTest.hpp"

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/implementation/Composition.hpp>
#include <core/connection/ConnectionFactory.hpp>

void LibraryTest::create()
{
  Library lib;
  CPPUNIT_ASSERT_EQUAL(size_t(0), lib.getComponents().size());
}

void LibraryTest::addComponent()
{
  Component *comp = ComponentFactory::produce("comp");
  Library lib;
  lib.addComponent(comp);
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

    void accept(Visitor &) {}
    void accept(ConstVisitor &) const {}

    bool &destructorCalled;
};

void LibraryTest::deleteComponent()
{
  bool deleted = false;
  Implementation *impl = new Implementation(deleted);
  Component *comp = new Component("comp", impl);
  Library lib;
  lib.addComponent(comp);
  CPPUNIT_ASSERT(lib.contains(comp));
  lib.deleteComponent(comp);

  CPPUNIT_ASSERT(!lib.contains(comp));
  CPPUNIT_ASSERT(deleted);
}

void LibraryTest::deleteComponentRemovesDepdantInstances()
{
  Component *comp1 = ComponentFactory::produce("comp1");
  Composition *composition = new Composition();
  Instance *inst = new Instance("inst", Point(0,0), comp1);
  composition->addInstance(inst);
  Component *comp2 = new Component("comp2", composition);

  Library lib;
  lib.addComponent(comp1);
  lib.addComponent(comp2);

  lib.deleteComponent(comp1);

  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getInstances().size());
}

void LibraryTest::deletsComponentsWhenDeleted()
{
  Library *lib = new Library();
  bool deleted = false;
  Implementation *impl = new Implementation(deleted);
  Component *comp = new Component("comp", impl);
  lib->addComponent(comp);
  delete lib;

  CPPUNIT_ASSERT(deleted);
}

void LibraryTest::getComponent()
{
  Component *comp = ComponentFactory::produce("comp");
  Library lib;
  lib.addComponent(comp);

  Component *ret = lib.getComponent("comp");
  CPPUNIT_ASSERT_EQUAL(comp, ret);
}

void LibraryTest::getCorrectComponent()
{
  Component *comp = ComponentFactory::produce("comp3");
  Library lib;
  lib.addComponent(ComponentFactory::produce("comp1"));
  lib.addComponent(ComponentFactory::produce("comp2"));
  lib.addComponent(comp);
  lib.addComponent(ComponentFactory::produce("comp4"));
  lib.addComponent(ComponentFactory::produce("comp5"));
  lib.addComponent(ComponentFactory::produce("comp6"));

  Component *ret = lib.getComponent("comp3");
  CPPUNIT_ASSERT_EQUAL(comp, ret);
}

void LibraryTest::throwErrorWhenComponentNotInLibrary()
{
  Library lib;
  CPPUNIT_ASSERT_THROW(lib.getComponent("lala"), std::invalid_argument);
}

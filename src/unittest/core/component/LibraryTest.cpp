// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "LibraryTest.hpp"
#include "../implementation/CompositionInstanceMock.hpp"

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
  lib.getComponents().add(comp);
  CPPUNIT_ASSERT(lib.getComponents().contains(comp));
}

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
  lib.getComponents().add(comp);
  CPPUNIT_ASSERT(lib.getComponents().contains(comp));
  lib.getComponents().remove(comp);

  CPPUNIT_ASSERT(!lib.getComponents().contains(comp));
  CPPUNIT_ASSERT(deleted);
}

void LibraryTest::deleteComponentRemovesDepdantInstances()
{
  Component *comp1 = ComponentFactory::produce("comp1");
  Composition *composition = new Composition(new CompositionInstanceMock());
  Instance *inst = new Instance("inst", Point(0,0), comp1);
  composition->getInstances().add(inst);
  Component *comp2 = new Component("comp2", composition);

  Library lib;
  lib.getComponents().add(comp1);
  lib.getComponents().add(comp2);

  lib.getComponents().remove(comp1);

  CPPUNIT_ASSERT_EQUAL(size_t(0), composition->getInstances().size());
}

void LibraryTest::deletsComponentsWhenDeleted()
{
  Library *lib = new Library();
  bool deleted = false;
  Implementation *impl = new Implementation(deleted);
  Component *comp = new Component("comp", impl);
  lib->getComponents().add(comp);
  delete lib;

  CPPUNIT_ASSERT(deleted);
}

void LibraryTest::getComponent()
{
  Component *comp = ComponentFactory::produce("comp");
  Library lib;
  lib.getComponents().add(comp);

  Component *ret = lib.getComponent("comp");
  CPPUNIT_ASSERT_EQUAL(comp, ret);
}

void LibraryTest::getCorrectComponent()
{
  Component *comp = ComponentFactory::produce("comp3");
  Library lib;
  lib.getComponents().add(ComponentFactory::produce("comp1"));
  lib.getComponents().add(ComponentFactory::produce("comp2"));
  lib.getComponents().add(comp);
  lib.getComponents().add(ComponentFactory::produce("comp4"));
  lib.getComponents().add(ComponentFactory::produce("comp5"));
  lib.getComponents().add(ComponentFactory::produce("comp6"));

  Component *ret = lib.getComponent("comp3");
  CPPUNIT_ASSERT_EQUAL(comp, ret);
}

void LibraryTest::throwErrorWhenComponentNotInLibrary()
{
  Library lib;
  CPPUNIT_ASSERT_THROW(lib.getComponent("lala"), std::invalid_argument);
}

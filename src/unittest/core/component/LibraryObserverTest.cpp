#include "LibraryObserverTest.hpp"

#include <core/component/Library.hpp>
#include <core/component/ComponentFactory.hpp>

class TestVirtual : public LibraryObserver
{
  public:
    TestVirtual(bool &aDestroyed) :
      destroyed(aDestroyed)
    {
    }

    ~TestVirtual()
    {
      destroyed = true;
    }

  private:
    bool &destroyed;

};

void LibraryObserverTest::destructorIsVirtual()
{
  bool destroyed = false;
  LibraryObserver *observer = new TestVirtual(destroyed);
  delete observer;
  CPPUNIT_ASSERT(destroyed);
}

void LibraryObserverTest::libraryInheritsObserverCollection()
{
  Library library;
  ObserverCollection<LibraryObserver> *observerCollection = dynamic_cast<ObserverCollection<LibraryObserver>*>(&library);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

class LibraryTestObserver : public LibraryObserver
{
  public:
    LibraryTestObserver() :
      newComponents(),
      delComponents()
    {
    }

    void addComponent(const Library *parent, Component *component)
    {
      (void)(parent);
      newComponents.push_back(component);
    }

    void delComponent(const Library *parent, Component *component)
    {
      (void)(parent);
      delComponents.push_back(component);
    }

    std::vector<Component*> newComponents;
    std::vector<Component*> delComponents;
};

void LibraryObserverTest::getInformedOnAdd()
{
  LibraryTestObserver observer;
  Library library;
  library.registerObserver(&observer);

  Component *component = ComponentFactory::produce("");
  library.add(component);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newComponents.size());
  CPPUNIT_ASSERT_EQUAL(component, observer.newComponents[0]);
}

void LibraryObserverTest::getInformedOnDelete()
{
  LibraryTestObserver observer;
  Library library;
  library.registerObserver(&observer);

  Component *component = ComponentFactory::produce("");
  library.add(component);
  library.del(component);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.delComponents.size());
  CPPUNIT_ASSERT_EQUAL(component, observer.delComponents[0]);
}

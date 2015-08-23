#include "ComponentPortObserverTest.hpp"

#include <core/component/Component.hpp>
#include <core/util/Observer.hpp>

class TestVirtualComponentPortObserver : public ComponentPortObserver
{
  public:
    TestVirtualComponentPortObserver(bool &aDestroyed) :
      destroyed(aDestroyed)
    {
    }

    ~TestVirtualComponentPortObserver()
    {
      destroyed = true;
    }

  private:
    bool &destroyed;

};

void ComponentPortObserverTest::destructor_is_virtual()
{
  bool destroyed = false;
  ComponentPortObserver *observer = new TestVirtualComponentPortObserver(destroyed);
  delete observer;
  CPPUNIT_ASSERT(destroyed);
}

void ComponentPortObserverTest::inherits_ObserverCollection()
{
  Signal port("");
  ObserverCollection<ComponentPortObserver> *observerCollection = dynamic_cast<ObserverCollection<ComponentPortObserver>*>(&port);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

class ComponentPortTestObserver : public ComponentPortObserver
{
  public:
    ComponentPortTestObserver() :
      newIndex(),
      newName()
    {
    }

    void topIndexChanged(size_t index)
    {
      newIndex.push_back(index);
    }

    void nameChanged(const std::string &name)
    {
      newName.push_back(name);
    }

    std::vector<size_t> newIndex;
    std::vector<std::string> newName;
};

void ComponentPortObserverTest::get_informed_on_topIndex_change()
{
  Signal port("");
  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setTopIndex(42);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newIndex.size());
  CPPUNIT_ASSERT_EQUAL(size_t(42), observer.newIndex[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::do_not_inform_if_topIndex_is_the_same()
{
  Signal port("");
  port.setTopIndex(42);

  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setTopIndex(42);

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newIndex.size());

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::get_informed_on_name_change()
{
  Signal port("");
  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setName("new name");

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newName.size());
  CPPUNIT_ASSERT_EQUAL(std::string("new name"), observer.newName[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::do_not_inform_if_name_is_the_same()
{
  Signal port("old name");
  port.setTopIndex(42);

  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setName("old name");

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newName.size());

  port.unregisterObserver(&observer);
}


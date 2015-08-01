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

void ComponentPortObserverTest::destructorIsVirtual()
{
  bool destroyed = false;
  ComponentPortObserver *observer = new TestVirtualComponentPortObserver(destroyed);
  delete observer;
  CPPUNIT_ASSERT(destroyed);
}

void ComponentPortObserverTest::inheritsObserverCollection()
{
  Signal port("");
  ObserverCollection<ComponentPortObserver> *observerCollection = dynamic_cast<ObserverCollection<ComponentPortObserver>*>(&port);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

class ComponentPortTestObserver : public ComponentPortObserver
{
  public:
    ComponentPortTestObserver() :
      newIndex()
    {
    }

    void topIndexChanged(size_t index)
    {
      newIndex.push_back(index);
    }

    std::vector<size_t> newIndex;
};

void ComponentPortObserverTest::getInformedOnTopIndexChange()
{
  Signal port("");
  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setTopIndex(42);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newIndex.size());
  CPPUNIT_ASSERT_EQUAL(size_t(42), observer.newIndex[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::doNotInformIfTopIndexIsTheSame()
{
  Signal port("");
  port.setTopIndex(42);

  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setTopIndex(42);

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newIndex.size());

  port.unregisterObserver(&observer);
}


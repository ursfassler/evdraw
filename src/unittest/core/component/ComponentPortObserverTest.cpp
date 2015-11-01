// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentPortObserverTest.hpp"
#include "ComponentPortObserverMock.hpp"

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
  ComponentPort port("", PortType::Signal);
  ObserverCollection<ComponentPortObserver> *observerCollection = dynamic_cast<ObserverCollection<ComponentPortObserver>*>(&port);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

void ComponentPortObserverTest::get_informed_on_topIndex_change()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortObserverMock observer;
  port.registerObserver(&observer);

  port.setTopIndex(42);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newIndex.size());
  CPPUNIT_ASSERT_EQUAL(size_t(42), observer.newIndex[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::do_not_inform_if_topIndex_is_the_same()
{
  ComponentPort port("", PortType::Signal);
  port.setTopIndex(42);

  ComponentPortObserverMock observer;
  port.registerObserver(&observer);

  port.setTopIndex(42);

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newIndex.size());

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::get_informed_on_name_change()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortObserverMock observer;
  port.registerObserver(&observer);

  port.setName("new name");

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.nameChanged_port.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<const ComponentPort*>(&port), observer.nameChanged_port[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::do_not_inform_if_name_is_the_same()
{
  ComponentPort port("old name", PortType::Signal);
  port.setTopIndex(42);

  ComponentPortObserverMock observer;
  port.registerObserver(&observer);

  port.setName("old name");

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.nameChanged_port.size());

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::get_informed_on_type_change()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortObserverMock observer;
  port.registerObserver(&observer);

  port.setType(PortType::Slot);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.typeChanged_port.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<const ComponentPort*>(&port), observer.typeChanged_port[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::do_not_inform_if_type_is_the_same()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortObserverMock observer;
  port.registerObserver(&observer);

  port.setType(PortType::Signal);

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.typeChanged_port.size());

  port.unregisterObserver(&observer);
}


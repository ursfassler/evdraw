// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

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
  ComponentPort port("", PortType::Signal);
  ObserverCollection<ComponentPortObserver> *observerCollection = dynamic_cast<ObserverCollection<ComponentPortObserver>*>(&port);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

class ComponentPortTestObserver : public ComponentPortObserver
{
  public:
    ComponentPortTestObserver() :
      newIndex(),
      newName(),
      newType()
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

    void typeChanged(PortType type)
    {
      newType.push_back(type);
    }

    std::vector<size_t> newIndex;
    std::vector<std::string> newName;
    std::vector<PortType> newType;
};

void ComponentPortObserverTest::get_informed_on_topIndex_change()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortTestObserver observer;
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

  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setTopIndex(42);

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newIndex.size());

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::get_informed_on_name_change()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setName("new name");

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newName.size());
  CPPUNIT_ASSERT_EQUAL(std::string("new name"), observer.newName[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::do_not_inform_if_name_is_the_same()
{
  ComponentPort port("old name", PortType::Signal);
  port.setTopIndex(42);

  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setName("old name");

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newName.size());

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::get_informed_on_type_change()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setType(PortType::Slot);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newType.size());
  CPPUNIT_ASSERT_EQUAL(PortType::Slot, observer.newType[0]);

  port.unregisterObserver(&observer);
}

void ComponentPortObserverTest::do_not_inform_if_type_is_the_same()
{
  ComponentPort port("", PortType::Signal);
  ComponentPortTestObserver observer;
  port.registerObserver(&observer);

  port.setType(PortType::Signal);

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newType.size());

  port.unregisterObserver(&observer);
}


// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentObserverTest.hpp"

#include "ComponentObserverMock.h"

#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/implementation/NullImplementation.hpp>
#include <core/util/Observer.hpp>

class TestVirtualComponentObserver : public ComponentObserver
{
  public:
    TestVirtualComponentObserver(bool &aDestroyed) :
      destroyed(aDestroyed)
    {
    }

    ~TestVirtualComponentObserver()
    {
      destroyed = true;
    }

  private:
    bool &destroyed;

};

void ComponentObserverTest::destructor_is_virtual()
{
  bool destroyed = false;
  ComponentObserver *observer = new TestVirtualComponentObserver(destroyed);
  delete observer;
  CPPUNIT_ASSERT(destroyed);
}

void ComponentObserverTest::inherits_ObserverCollection()
{
  Component component("", new NullImplementation());
  ObserverCollection<ComponentObserver> *observerCollection = dynamic_cast<ObserverCollection<ComponentObserver>*>(&component);
  CPPUNIT_ASSERT(observerCollection != nullptr);

  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_nameChanged()
{
  ComponentObserverMock observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  component.setName("new name");

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.nameChanged_item.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<IComponent*>(&component), observer.nameChanged_item[0]);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::do_not_notify_if_name_is_the_same()
{
  ComponentObserverMock observer;
  Component component("theName", new NullImplementation());
  component.registerObserver(&observer);

  component.setName("theName");

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.nameChanged_item.size());

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_heightChanged_on_addPort()
{
  ComponentObserverMock observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component.getPorts().add(port);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), observer.changedHeights);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_heightChanged_on_deletePort()
{
  Component component("", new NullImplementation());
  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component.getPorts().add(port);

  ComponentObserverMock observer;
  CPPUNIT_ASSERT_EQUAL(unsigned(0), observer.changedHeights);
  component.registerObserver(&observer);
  component.getPorts().remove(port);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), observer.changedHeights);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_heightChanged_on_portTypeChange()
{
  Component component("", new NullImplementation());
  component.getPorts().add(new ComponentPort("1", PortType::Signal));
  ComponentPort *port = new ComponentPort("2", PortType::Signal);
  component.getPorts().add(port);

  ComponentObserverMock observer;
  CPPUNIT_ASSERT_EQUAL(unsigned(0), observer.changedHeights);
  component.registerObserver(&observer);

  port->setType(PortType::Slot);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), observer.changedHeights);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

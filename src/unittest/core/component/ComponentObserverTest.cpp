// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentObserverTest.hpp"


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

class ComponentTestObserver : public ComponentObserver
{
  public:
    ComponentTestObserver() :
      newPorts(),
      delPorts(),
      newName()
    {
    }

    void portAdded(ComponentPort *port)
    {
      newPorts.push_back(port);
    }

    void portDeleted(ComponentPort *port)
    {
      delPorts.push_back(port);
    }

    void heightChanged()
    {
      changedHeights++;
    }

    void nameChanged(const std::string &name)
    {
      newName.push_back(name);
    }

    std::vector<ComponentPort*> newPorts;
    std::vector<ComponentPort*> delPorts;
    unsigned changedHeights = 0;
    std::vector<std::string> newName;
};

void ComponentObserverTest::notify_nameChanged()
{
  ComponentTestObserver observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  component.setName("new name");

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newName.size());
  CPPUNIT_ASSERT_EQUAL(std::string("new name"), observer.newName[0]);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::do_not_notify_if_name_is_the_same()
{
  ComponentTestObserver observer;
  Component component("theName", new NullImplementation());
  component.registerObserver(&observer);

  component.setName("theName");

  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.newName.size());

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_portAdded()
{
  ComponentTestObserver observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component.addPort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newPorts.size());
  CPPUNIT_ASSERT_EQUAL(port, observer.newPorts[0]);

  component.unregisterObserver(&observer);
  component.deletePort(port);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_portDeleted()
{
  ComponentTestObserver observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component.addPort(port);
  component.deletePort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.delPorts.size());
  CPPUNIT_ASSERT_EQUAL(port, observer.delPorts[0]);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_heightChanged_on_addPort()
{
  ComponentTestObserver observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component.addPort(port);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), observer.changedHeights);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_heightChanged_on_deletePort()
{
  Component component("", new NullImplementation());
  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component.addPort(port);

  ComponentTestObserver observer;
  CPPUNIT_ASSERT_EQUAL(unsigned(0), observer.changedHeights);
  component.registerObserver(&observer);
  component.deletePort(port);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), observer.changedHeights);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

void ComponentObserverTest::notify_heightChanged_on_portTypeChange()
{
  Component component("", new NullImplementation());
  component.addPort(new ComponentPort("1", PortType::Signal));
  ComponentPort *port = new ComponentPort("2", PortType::Signal);
  component.addPort(port);

  ComponentTestObserver observer;
  CPPUNIT_ASSERT_EQUAL(unsigned(0), observer.changedHeights);
  component.registerObserver(&observer);

  port->setType(PortType::Slot);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), observer.changedHeights);

  component.unregisterObserver(&observer);
  ComponentFactory::cleanup(component);
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceObserverTest.hpp"

#include "InstanceObserverMock.h"

#include <core/util/Observer.hpp>
#include <core/implementation/NullImplementation.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/SimplePort.hpp>

#include <core/util/contract.hpp>

void InstanceObserverTest::setUp()
{
  precondition(component == nullptr);
  precondition(instance == nullptr);

  component = ComponentFactory::produce("Component", {"in"}, {"out"});
  instance = InstanceFactory::produce(component, "instance", Point(0,0));
}

void InstanceObserverTest::tearDown()
{
  precondition(component != nullptr);
  precondition(instance != nullptr);

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);

  instance = nullptr;
  component = nullptr;
}

void InstanceObserverTest::destructorIsVirtual()
{
  bool destroyed = false;
  InstanceObserver *observer = new InstanceObserverMock(&destroyed);
  delete observer;
  CPPUNIT_ASSERT(destroyed);
}

void InstanceObserverTest::inheritsObserverCollection()
{
  ObserverCollection<InstanceObserver> *observerCollection = dynamic_cast<ObserverCollection<InstanceObserver>*>(instance);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

void InstanceObserverTest::notify_addPort()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(size_t(2), instance->getPorts().size());

  component->addPort(new ComponentPort("sig", PortType::Signal));

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.addedPorts.size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(static_cast<IPort*>(instance->getPorts()[2]), observer.addedPorts[0]);

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::notify_delPort()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(size_t(2), instance->getPorts().size());

  IPort *port = instance->getPorts()[0];
  component->deletePort(component->getPorts()[0]);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.deletedPorts.size());
  CPPUNIT_ASSERT_EQUAL(port, observer.deletedPorts[0]);
  CPPUNIT_ASSERT_EQUAL(size_t(1), instance->getPorts().size());

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::notify_height_changed_on_port_type_change()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  InstancePort *port = instance->getPorts()[0];
  port->getCompPort()->setType(PortType::Signal);

  CPPUNIT_ASSERT_EQUAL(uint(1), observer.changedHeight);

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::notify_height_changed_on_addPort()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  component->addPort(new ComponentPort("3", PortType::Signal));

  CPPUNIT_ASSERT_EQUAL(uint(1), observer.changedHeight);

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::notify_height_changed_on_deletePort()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  component->deletePort(component->getPorts()[0]);
  CPPUNIT_ASSERT_EQUAL(uint(0), observer.changedHeight);
  component->deletePort(component->getPorts()[0]);
  CPPUNIT_ASSERT_EQUAL(uint(1), observer.changedHeight);

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::notify_setName()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  instance->setName("new name");
  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.nameChanged_instance.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<const IInstance*>(instance), observer.nameChanged_instance[0]);

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::no_notify_when_set_same_name()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  instance->setName(instance->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), observer.nameChanged_instance.size());

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::notify_on_component_name_change()
{
  InstanceObserverMock observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  component->setName("new name");
  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.componentNameChanged_instance.size());
  CPPUNIT_ASSERT_EQUAL(static_cast<const IInstance*>(instance), observer.componentNameChanged_instance[0]);
  CPPUNIT_ASSERT_EQUAL(std::string("new name"), instance->getComponent()->getName());

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

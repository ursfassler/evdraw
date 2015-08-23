// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceObserverTest.hpp"

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

class TestVirtualInstanceObserver : public InstanceObserver
{
  public:
    TestVirtualInstanceObserver(bool &aDestroyed) :
      destroyed(aDestroyed)
    {
    }

    ~TestVirtualInstanceObserver()
    {
      destroyed = true;
    }

  private:
    bool &destroyed;

};

void InstanceObserverTest::destructorIsVirtual()
{
  bool destroyed = false;
  InstanceObserver *observer = new TestVirtualInstanceObserver(destroyed);
  delete observer;
  CPPUNIT_ASSERT(destroyed);
}

void InstanceObserverTest::inheritsObserverCollection()
{
  ObserverCollection<InstanceObserver> *observerCollection = dynamic_cast<ObserverCollection<InstanceObserver>*>(instance);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

class TestInstanceObserver : public InstanceObserver
{
  public:
    TestInstanceObserver() :
      addedPorts(),
      deletedPorts()
    {
    }

    void portAdded(InstancePort *port)
    {
      addedPorts.push_back(port);
    }
    std::vector<InstancePort*> addedPorts;

    void portDeleted(InstancePort *port)
    {
      deletedPorts.push_back(port);
    }
    std::vector<InstancePort*> deletedPorts;

};

void InstanceObserverTest::notifyAddPort()
{
  TestInstanceObserver observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(size_t(2), instance->getPorts().size());

  component->addPort(new Signal("sig"));

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.addedPorts.size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), instance->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(instance->getPorts()[2], observer.addedPorts[0]);

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

void InstanceObserverTest::notifyDelPort()
{
  TestInstanceObserver observer;
  instance->ObserverCollection<InstanceObserver>::registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(size_t(2), instance->getPorts().size());

  InstancePort *port = instance->getPorts()[0];
  component->deletePort(component->getPorts()[0]);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.deletedPorts.size());
  CPPUNIT_ASSERT_EQUAL(port, observer.deletedPorts[0]);
  CPPUNIT_ASSERT_EQUAL(size_t(1), instance->getPorts().size());

  instance->ObserverCollection<InstanceObserver>::unregisterObserver(&observer);
}

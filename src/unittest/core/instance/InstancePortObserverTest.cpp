// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstancePortObserverTest.hpp"

void InstancePortObserverTest::setUp()
{
  component = new ComponentPort("", PortType::Signal);
  instance = new DummyInstance();
  port = new InstancePort(instance, component);
}

void InstancePortObserverTest::tearDown()
{
  delete port;
  port = nullptr;
  delete instance;
  instance = nullptr;
  delete component;
  component = nullptr;
}

class TestInstancePortObserver : public InstancePortObserver
{
  public:
    TestInstancePortObserver(bool &aDestructorCalled) :
      newName(),
      destructorCalled(aDestructorCalled)
    {
    }

    ~TestInstancePortObserver()
    {
      destructorCalled = true;
    }

    void nameChanged(const std::string &name)
    {
      newName.push_back(name);
    }

    std::vector<std::string> newName;

  private:
    bool &destructorCalled;
};

void InstancePortObserverTest::destructor_is_virtual()
{
  bool destructorCalled = false;
  InstancePortObserver *observer = new TestInstancePortObserver(destructorCalled);
  delete observer;
  CPPUNIT_ASSERT(destructorCalled);
}

void InstancePortObserverTest::inherits_ObserverCollection()
{
  CPPUNIT_ASSERT(dynamic_cast<ObserverCollection<InstancePortObserver>*>(port) != nullptr);
}

void InstancePortObserverTest::notify_on_name_change()
{
  bool destructorCalled = false;
  TestInstancePortObserver *observer = new TestInstancePortObserver(destructorCalled);
  port->ObserverCollection<InstancePortObserver>::registerObserver(observer);

  component->setName("test");
  CPPUNIT_ASSERT_EQUAL(size_t(1), observer->newName.size());
  CPPUNIT_ASSERT_EQUAL(std::string("test"), observer->newName[0]);

  port->ObserverCollection<InstancePortObserver>::unregisterObserver(observer);
  delete observer;
}

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

void ComponentObserverTest::destructorIsVirtual()
{
  bool destroyed = false;
  ComponentObserver *observer = new TestVirtualComponentObserver(destroyed);
  delete observer;
  CPPUNIT_ASSERT(destroyed);
}

void ComponentObserverTest::inheritsObserverCollection()
{
  Component component("", new NullImplementation());
  ObserverCollection<ComponentObserver> *observerCollection = dynamic_cast<ObserverCollection<ComponentObserver>*>(&component);
  CPPUNIT_ASSERT(observerCollection != nullptr);
}

class ComponentTestObserver : public ComponentObserver
{
  public:
    ComponentTestObserver() :
      newPorts(),
      delPorts()
    {
    }

    void portAdded(const Component *parent, ComponentPort *port)
    {
      (void)(parent);
      newPorts.push_back(port);
    }

    void portDeleted(const Component *parent, ComponentPort *port)
    {
      (void)(parent);
      delPorts.push_back(port);
    }

    std::vector<ComponentPort*> newPorts;
    std::vector<ComponentPort*> delPorts;
};

void ComponentObserverTest::getInformedOnAdd()
{
  ComponentTestObserver observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  ComponentPort *port = new Signal("");
  component.addPort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.newPorts.size());
  CPPUNIT_ASSERT_EQUAL(port, observer.newPorts[0]);

  delete port;
}

void ComponentObserverTest::getInformedOnDelete()
{
  ComponentTestObserver observer;
  Component component("", new NullImplementation());
  component.registerObserver(&observer);

  ComponentPort *port = new Signal("");
  component.addPort(port);
  component.delPort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.delPorts.size());
  CPPUNIT_ASSERT_EQUAL(port, observer.delPorts[0]);
}

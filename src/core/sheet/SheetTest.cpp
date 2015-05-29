#include "SheetTest.hpp"

#include "Sheet.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentFactory.hpp"
#include "../instance/Instance.hpp"
#include "../instance/InstanceFactory.hpp"
#include "../connection/ConnectionFactory.hpp"

void SheetTest::create()
{
  Sheet sheet;

  CPPUNIT_ASSERT_EQUAL(size_t(0), sheet.getInstances().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), sheet.getConnections().size());
}

void SheetTest::addInstance()
{
  Sheet sheet;
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  sheet.addInstance(instance);
  CPPUNIT_ASSERT_EQUAL(size_t(1), sheet.getInstances().size());
  CPPUNIT_ASSERT_EQUAL(instance, sheet.getInstances()[0]);

  ComponentFactory::dispose(component);
}

void SheetTest::addConnection()
{
  Sheet sheet;
  Connection *connection = ConnectionFactory::produce({10, 20, 30, 40, 50});

  sheet.addConnection(connection);
  CPPUNIT_ASSERT_EQUAL(size_t(1), sheet.getConnections().size());
  CPPUNIT_ASSERT_EQUAL(connection, sheet.getConnections()[0]);
}

class SheetObserverTest : public SheetObserver
{
  public:
    virtual void instanceAdded(Instance *instance)
    {
      lastInstanceAdded = instance;
    }

    virtual void connectionAdded(Connection *connection)
    {
      lastConnectionAdded = connection;
    }

    virtual void abortConnectionUnderConnstruction(PartialConnectionFromStart *connection)
    {
      lastAbortConnectionUnderConnstruction = connection;
    }

    virtual void addConnectionUnderConnstruction(PartialConnectionFromStart *connection)
    {
      lastAddConnectionUnderConnstruction = connection;
    }

    Instance *lastInstanceAdded = nullptr;
    Connection *lastConnectionAdded = nullptr;
    PartialConnectionFromStart *lastAbortConnectionUnderConnstruction = nullptr;
    PartialConnectionFromStart *lastAddConnectionUnderConnstruction = nullptr;
};

void SheetTest::notifyWhenAddInstance()
{
  Sheet sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);

  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));

  sheet.addInstance(instance);

  CPPUNIT_ASSERT_EQUAL(instance, observer.lastInstanceAdded);

  sheet.unregisterObserver(&observer);
}

void SheetTest::notifyWhenAddConnection()
{
  Sheet sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);

  Connection *connection = ConnectionFactory::produce({10, 20, 30, 40, 50});
  sheet.addConnection(connection);

  CPPUNIT_ASSERT_EQUAL(connection, observer.lastConnectionAdded);

  sheet.unregisterObserver(&observer);
}

void SheetTest::connectionUnderConstruction()
{
  Sheet sheet;

  CPPUNIT_ASSERT_EQUAL(static_cast<PartialConnectionFromStart*>(nullptr), sheet.getConnectionUnderConstruction());
  PartialConnectionFromStart *connection = new PartialConnectionFromStart();
  sheet.setConnectionUnderConstruction(connection);
  CPPUNIT_ASSERT_EQUAL(connection, sheet.getConnectionUnderConstruction());
}

void SheetTest::addConnectionUnderConstructionNotifiesObserver()
{
  Sheet sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);
  PartialConnectionFromStart *connection = new PartialConnectionFromStart();

  sheet.setConnectionUnderConstruction(connection);
  CPPUNIT_ASSERT_EQUAL(connection, observer.lastAddConnectionUnderConnstruction);

  sheet.unregisterObserver(&observer);
}

void SheetTest::overwriteConnectionUnderConstructionNotifiesObserver()
{
  Sheet sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);
  PartialConnectionFromStart *connection = new PartialConnectionFromStart();
  sheet.setConnectionUnderConstruction(connection);

  CPPUNIT_ASSERT_EQUAL(static_cast<PartialConnectionFromStart*>(nullptr), observer.lastAbortConnectionUnderConnstruction);
  sheet.setConnectionUnderConstruction(new PartialConnectionFromStart());
  CPPUNIT_ASSERT_EQUAL(connection, observer.lastAbortConnectionUnderConnstruction);

  sheet.unregisterObserver(&observer);
}

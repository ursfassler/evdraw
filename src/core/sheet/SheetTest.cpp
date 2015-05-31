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

    virtual void removeConnectionUnderConnstruction(Connection *connection)
    {
      lastRemoveConnectionUnderConnstruction = connection;
    }

    virtual void addConnectionUnderConnstruction(Connection *connection)
    {
      lastAddConnectionUnderConnstruction = connection;
    }

    Instance *lastInstanceAdded = nullptr;
    Connection *lastConnectionAdded = nullptr;
    Connection *lastRemoveConnectionUnderConnstruction = nullptr;
    Connection *lastAddConnectionUnderConnstruction = nullptr;
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

  CPPUNIT_ASSERT_EQUAL(static_cast<Connection*>(nullptr), sheet.getConnectionUnderConstruction());
  Connection *connection = new Connection();
  InstancePort rootPort(nullptr, nullptr, Point(0,0));
  sheet.setConnectionUnderConstruction(connection, &rootPort);
  CPPUNIT_ASSERT_EQUAL(connection, sheet.getConnectionUnderConstruction());
  CPPUNIT_ASSERT_EQUAL(&rootPort, sheet.getRootPort());
}

void SheetTest::addConnectionUnderConstructionNotifiesObserver()
{
  Sheet sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);
  InstancePort rootPort(nullptr, nullptr, Point(0,0));
  Connection *connection = new Connection();

  sheet.setConnectionUnderConstruction(connection, &rootPort);
  CPPUNIT_ASSERT_EQUAL(connection, observer.lastAddConnectionUnderConnstruction);

  sheet.unregisterObserver(&observer);
}

void SheetTest::canNotOverwriteConnectionUnderConstructio()
{
  Sheet sheet;
  Connection *connection = new Connection();
  InstancePort rootPort(nullptr, nullptr, Point(0,0));
  sheet.setConnectionUnderConstruction(connection, &rootPort);

  CPPUNIT_ASSERT_THROW(sheet.setConnectionUnderConstruction(new Connection(), &rootPort), PreconditionError);
}

void SheetTest::finishConnectionCreation()
{
  Sheet sheet;
  Connection *connection = new Connection();
  InstancePort rootPort(nullptr, nullptr, Point(0,0));
  sheet.setConnectionUnderConstruction(connection, &rootPort);

  SheetObserverTest observer;
  sheet.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<Connection*>(nullptr), observer.lastRemoveConnectionUnderConnstruction);
  sheet.removeConnectionUnderConstruction();
  CPPUNIT_ASSERT_EQUAL(connection, observer.lastRemoveConnectionUnderConnstruction);

  sheet.unregisterObserver(&observer);
}

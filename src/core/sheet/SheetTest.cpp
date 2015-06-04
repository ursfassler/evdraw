#include "SheetTest.hpp"

#include "Sheet.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentFactory.hpp"
#include "../instance/Instance.hpp"
#include "../instance/InstanceFactory.hpp"
#include "../connection/ConnectionFactory.hpp"
#include "../connection/SimplePort.hpp"

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
  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});

  Sheet sheet;
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

    virtual void finishConnectionUnderConstruction(Connection *connection)
    {
      lastFinishConnectionUnderConstruction = connection;
    }

    virtual void addConnectionUnderConstruction(Connection *connection)
    {
      lastAddConnectionUnderConstruction = connection;
    }

    Instance *lastInstanceAdded = nullptr;
    Connection *lastConnectionAdded = nullptr;
    Connection *lastFinishConnectionUnderConstruction = nullptr;
    Connection *lastAddConnectionUnderConstruction = nullptr;
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

  SimplePort startPort;
  SimplePort endPort;
  Connection *connection = ConnectionFactory::produce(&startPort, &endPort, {10, 20, 30, 40, 50});
  sheet.addConnection(connection);

  CPPUNIT_ASSERT_EQUAL(connection, observer.lastConnectionAdded);

  sheet.unregisterObserver(&observer);
}

void SheetTest::connectionUnderConstruction()
{
  Sheet sheet;

  CPPUNIT_ASSERT_EQUAL(static_cast<Connection*>(nullptr), sheet.getConnectionUnderConstruction());
  Instance instance("", Point(0,0), nullptr);
  InstancePort startPort(&instance, nullptr, Point(0,0));
  InstancePort endPort(&instance, nullptr, Point(0,0));
  sheet.startConnectionConstruction(&startPort, &endPort);
//  CPPUNIT_ASSERT_EQUAL(size_t(1), startPort.getConnector().getPoints().size());
//  CPPUNIT_ASSERT_EQUAL(startPort.getConnector().getPoints()[0], sheet.getConnectionUnderConstruction()->getStartPort());
}

void SheetTest::addConnectionUnderConstructionNotifiesObserver()
{
  Sheet sheet;
  SheetObserverTest observer;
  sheet.registerObserver(&observer);
  Instance instance("", Point(0,0), nullptr);
  InstancePort startPort(&instance, nullptr, Point(0,0));
  InstancePort endPort(&instance, nullptr, Point(0,0));

  sheet.startConnectionConstruction(&startPort, &endPort);
  CPPUNIT_ASSERT_EQUAL(sheet.getConnectionUnderConstruction(), observer.lastAddConnectionUnderConstruction);

  sheet.unregisterObserver(&observer);
}

void SheetTest::canNotOverwriteConnectionUnderConstructio()
{
  Sheet sheet;
  Instance instance("", Point(0,0), nullptr);
  InstancePort startPort(&instance, nullptr, Point(0,0));
  InstancePort endPort(&instance, nullptr, Point(0,0));
  sheet.startConnectionConstruction(&startPort, &endPort);

  CPPUNIT_ASSERT_THROW(sheet.startConnectionConstruction(&startPort, &endPort), PreconditionError);
}

void SheetTest::finishConnectionCreation()
{
//  Sheet sheet;
//  InstancePort startPort(nullptr, nullptr, Point(0,0));
//  InstancePort tmpEnd(nullptr, nullptr, Point(0,0));
//  InstancePort endPort(nullptr, nullptr, Point(0,0));
//  sheet.startConnectionConstruction(&startPort, &tmpEnd);
//  Connection *connection = sheet.getConnectionUnderConstruction();

//  SheetObserverTest observer;
//  sheet.registerObserver(&observer);

//  CPPUNIT_ASSERT_EQUAL(static_cast<Connection*>(nullptr), observer.lastFinishConnectionUnderConstruction);
//  sheet.finishConnectionConstruction(&endPort);
//  CPPUNIT_ASSERT_EQUAL(connection, observer.lastFinishConnectionUnderConstruction);
//  CPPUNIT_ASSERT_EQUAL(connection, observer.lastConnectionAdded);

//  CPPUNIT_ASSERT_EQUAL(size_t(1), sheet.getConnections().size());
//  CPPUNIT_ASSERT_EQUAL(connection, sheet.getConnections()[0]);
//  CPPUNIT_ASSERT(!sheet.hasConnectionUnderConstruction());

//  sheet.unregisterObserver(&observer);
}

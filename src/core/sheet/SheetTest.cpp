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

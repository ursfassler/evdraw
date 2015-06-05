#include "RizzlyPrintTest.hpp"

#include "RizzlyPrint.hpp"
#include "../core/component/ComponentFactory.hpp"
#include "../core/instance/InstanceFactory.hpp"
#include "../core/connection/ConnectionFactory.hpp"

#include <sstream>

void RizzlyPrintTest::printEmpty()
{
  std::stringstream ss;
  RizzlyPrint printer(ss);
  Sheet sheet;

  printer.print(sheet);

  CPPUNIT_ASSERT_EQUAL(std::string(""), ss.str());
}

void RizzlyPrintTest::onlyInstance()
{
  std::stringstream ss;
  RizzlyPrint printer(ss);
  Sheet sheet;
  Component *component = ComponentFactory::produce("Component", {}, {});
  Instance *instance = InstanceFactory::produce(component, "instance", Point(0,0));
  sheet.addInstance(instance);

  printer.print(sheet);

  CPPUNIT_ASSERT_EQUAL(std::string("instance: Component;\n"), ss.str());

  ComponentFactory::dispose(component);
}

void RizzlyPrintTest::connection()
{
  std::stringstream ss;
  RizzlyPrint printer(ss);
  Sheet sheet;
  Component *component = ComponentFactory::produce("Component", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  sheet.addInstance(instance);
  Connection *connection = ConnectionFactory::produce(instance->getPorts().front(), instance->getPorts().back());
  sheet.addConnection(connection);

  printer.print(sheet);

  CPPUNIT_ASSERT_EQUAL(std::string("inst: Component;\ninst.a -> inst.b;\n"), ss.str());

  ComponentFactory::dispose(component);
}

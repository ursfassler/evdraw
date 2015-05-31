#include "RizzlyPrintTest.hpp"

#include "RizzlyPrint.hpp"
#include "../core/component/ComponentFactory.hpp"
#include "../core/instance/InstanceFactory.hpp"

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

  CPPUNIT_ASSERT_EQUAL(std::string("instance: Component;"), ss.str());

  ComponentFactory::dispose(component);
}

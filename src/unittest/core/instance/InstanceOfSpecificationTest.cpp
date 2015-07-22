#include "InstanceOfSpecificationTest.hpp"

#include <core/instance/InstanceOfSpecification.hpp>
#include <core/specification/Specification.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/component/ComponentFactory.hpp>

void InstanceOfSpecificationTest::setUp()
{
  component = ComponentFactory::produce("component");
  instance = InstanceFactory::produce(component, "instance", Point(0,0));
}

void InstanceOfSpecificationTest::tearDown()
{
  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
  instance = nullptr;
  component = nullptr;
}

void InstanceOfSpecificationTest::inheritsSpecification()
{
  InstanceOfSpecification ios(nullptr);

  CPPUNIT_ASSERT(dynamic_cast<Specification*>(&ios) != nullptr);
}

void InstanceOfSpecificationTest::copyConstructor()
{
  InstanceOfSpecification ios1(component);
  InstanceOfSpecification ios2(ios1);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Component*>(component), ios2.component);
}

void InstanceOfSpecificationTest::assignOperator()
{
  InstanceOfSpecification ios1(component);
  InstanceOfSpecification ios2(nullptr);

  ios2 = ios1;

  CPPUNIT_ASSERT_EQUAL(static_cast<const Component*>(component), ios2.component);
}

void InstanceOfSpecificationTest::satisfied()
{
  InstanceOfSpecification ios(component);
  CPPUNIT_ASSERT(ios.isSatisfiedBy(instance));
}

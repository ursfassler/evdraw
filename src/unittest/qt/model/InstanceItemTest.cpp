// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceItemTest.hpp"

#include <qt/model/INameTypeItem.hpp>
#include <core/instance/IComponentInstance.hpp>

void InstanceItemTest::setUp()
{
  testee.added(&instance);
}

void InstanceItemTest::tearDown()
{
  testee.removed(&instance);
  components.clear();
  instance.name = "";
  instance.component = nullptr;
}

void InstanceItemTest::inherits_INameTypeItem()
{
  CPPUNIT_ASSERT(dynamic_cast<INameTypeItem<IComponentInstance>*>(&testee) != nullptr);
}

void InstanceItemTest::type_is_not_editable()
{
  CPPUNIT_ASSERT_EQUAL(false, testee.isTypeEditable());
}

void InstanceItemTest::read_type()
{
  ComponentMock *component = new ComponentMock();

  components.add(new ComponentMock());
  components.add(new ComponentMock());
  components.add(component);
  components.add(new ComponentMock());

  instance.component = component;

  CPPUNIT_ASSERT_EQUAL(unsigned(2), testee.getType(&instance));
}

void InstanceItemTest::has_a_type_model()
{
  CPPUNIT_ASSERT(testee.getTypeModel() != nullptr);
}

void InstanceItemTest::read_name()
{
  instance.name = "the name";

  CPPUNIT_ASSERT_EQUAL(std::string("the name"), testee.getName(&instance));
}

void InstanceItemTest::change_name()
{
  testee.setName(&instance, "a new name");

  CPPUNIT_ASSERT_EQUAL(true, testee.isNameEditable());
  CPPUNIT_ASSERT_EQUAL(std::string("a new name"), instance.name);
}

void InstanceItemTest::notify_name_change()
{
  IInstance *changedName{nullptr};
  testee.addNameListener([&changedName](IInstance *item)
  {
    changedName = item;
  });

  instance.notify_nameChange();

  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(&instance), changedName);
}

void InstanceItemTest::notify_type_change()
{
  IInstance *changedType{nullptr};
  testee.addTypeListener([&changedType](IInstance *item)
  {
    changedType = item;
  });

  instance.notify_typeChange();

  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(&instance), changedType);
}


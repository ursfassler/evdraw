// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentItemTest.hpp"

#include <qt/model/INameTypeItem.hpp>
#include <core/component/Component.hpp>
#include <core/implementation/ImplementationType.hpp>

void ComponentItemTest::setUp()
{
  component.implementation = &implementation;
  testee.added(&component);
}

void ComponentItemTest::tearDown()
{
  testee.removed(&component);
}

void ComponentItemTest::inherits_INameTypeItem()
{
  CPPUNIT_ASSERT(dynamic_cast<INameTypeItem<IComponent>*>(&testee) != nullptr);
}

void ComponentItemTest::type_is_not_editable()
{
  CPPUNIT_ASSERT_EQUAL(false, testee.isTypeEditable());
}

void ComponentItemTest::read_name()
{
  component.name = "the name";

  CPPUNIT_ASSERT_EQUAL(std::string("the name"), testee.getName(&component));
}

void ComponentItemTest::read_type()
{
  implementation.type = ImplementationType::Empty;
  CPPUNIT_ASSERT_EQUAL(uintFromImplementationType(ImplementationType::Empty), testee.getType(&component));

  implementation.type = ImplementationType::Composition;
  CPPUNIT_ASSERT_EQUAL(uintFromImplementationType(ImplementationType::Composition), testee.getType(&component));
}

void ComponentItemTest::change_name()
{
  CPPUNIT_ASSERT_EQUAL(true, testee.isNameEditable());

  testee.setName(&component, "a new name");

  CPPUNIT_ASSERT_EQUAL(std::string("a new name"), component.name);
}

void ComponentItemTest::get_notified_on_name_change()
{
  IComponent *changedNameItem{nullptr};
  const auto listener = [&changedNameItem](IComponent *item)
  {
    changedNameItem = item;
  };
  testee.addNameListener(listener);

  component.notify_nameChange();

  CPPUNIT_ASSERT_EQUAL(static_cast<IComponent*>(&component), changedNameItem);
}

void ComponentItemTest::has_a_type_model()
{
  CPPUNIT_ASSERT(testee.getTypeModel() != nullptr);
}


// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortItemTest.hpp"

#include <qtmodel/INameTypeItem.hpp>
#include <core/component/ComponentPort.hpp>

void PortItemTest::setUp()
{
  testee.added(&port);
}

void PortItemTest::tearDown()
{
  testee.removed(&port);
//  components.clear();
  port.setName("");
  port.setType(PortType::Signal);
//  instance.component = nullptr;
}

void PortItemTest::inherits_INameTypeItem()
{
  CPPUNIT_ASSERT(dynamic_cast<INameTypeItem<ComponentPort>*>(&testee) != nullptr);
}

void PortItemTest::has_a_type_model()
{
  CPPUNIT_ASSERT(testee.getTypeModel() != nullptr);
}

void PortItemTest::read_type()
{
  port.setType(PortType::Signal);
  CPPUNIT_ASSERT_EQUAL(uintFromPortType(PortType::Signal), testee.getType(&port));

  port.setType(PortType::Slot);
  CPPUNIT_ASSERT_EQUAL(uintFromPortType(PortType::Slot), testee.getType(&port));
}

void PortItemTest::change_type()
{
  testee.setType(&port, uintFromPortType(PortType::Slot));

  CPPUNIT_ASSERT_EQUAL(true, testee.isTypeEditable());
  CPPUNIT_ASSERT_EQUAL(PortType::Slot, port.getType());
}

void PortItemTest::notify_type_change()
{
  ComponentPort *changedType{nullptr};
  testee.addTypeListener([&changedType](ComponentPort *item)
  {
    changedType = item;
  });

  port.setType(PortType::Slot);

  CPPUNIT_ASSERT_EQUAL(static_cast<ComponentPort*>(&port), changedType);
}

void PortItemTest::read_name()
{
  port.setName("the name");

  CPPUNIT_ASSERT_EQUAL(std::string("the name"), testee.getName(&port));
}

void PortItemTest::change_name()
{
  testee.setName(&port, "a new name");

  CPPUNIT_ASSERT_EQUAL(true, testee.isNameEditable());
  CPPUNIT_ASSERT_EQUAL(std::string("a new name"), port.getName());
}

void PortItemTest::notify_name_change()
{
  ComponentPort *changedName{nullptr};
  testee.addNameListener([&changedName](ComponentPort *item)
  {
    changedName = item;
  });

  port.setName("test");

  CPPUNIT_ASSERT_EQUAL(static_cast<ComponentPort*>(&port), changedName);
}


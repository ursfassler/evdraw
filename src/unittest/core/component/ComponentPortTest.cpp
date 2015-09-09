// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentPortTest.hpp"

#include <core/component/ComponentPort.hpp>
#include <core/component/PortType.hpp>

#include <string>

void ComponentPortTest::create()
{
  ComponentPort port("hallo", PortType::Signal);
  CPPUNIT_ASSERT_EQUAL(std::string("hallo"), port.getName());
  CPPUNIT_ASSERT_EQUAL(PortType::Signal, port.getType());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port.getTopIndex());
}

void ComponentPortTest::setTopIndex()
{
  ComponentPort port("hallo", PortType::Signal);
  port.setTopIndex(42);
  CPPUNIT_ASSERT_EQUAL(size_t(42), port.getTopIndex());
}

void ComponentPortTest::setName()
{
  ComponentPort port("hallo", PortType::Signal);

  port.setName("port test name");
  CPPUNIT_ASSERT_EQUAL(std::string("port test name"), port.getName());
}

void ComponentPortTest::setType()
{
  ComponentPort port("", PortType::Signal);

  port.setType(PortType::Slot);
  CPPUNIT_ASSERT_EQUAL(PortType::Slot, port.getType());
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortTypeTest.h"

#include <core/component/PortType.hpp>
#include <core/types.hpp>
#include <core/util/list.hpp>

#include <string>
#include <sstream>
#include <vector>

void PortTypeTest::portTypeList_contains_signal()
{
  const std::vector<PortType> list = portTypeList();
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), PortType::Signal));
}

void PortTypeTest::portTypeList_contains_slot()
{
  const std::vector<PortType> list = portTypeList();
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), PortType::Slot));
}

void PortTypeTest::signal_toString()
{
  CPPUNIT_ASSERT_EQUAL(std::string("signal"), toString(PortType::Signal));
}

void PortTypeTest::slot_toString()
{
  CPPUNIT_ASSERT_EQUAL(std::string("slot"), toString(PortType::Slot));
}

void PortTypeTest::toString_is_defined_for_all()
{
  for (PortType type : portTypeList()) {
    CPPUNIT_ASSERT_NO_THROW(toString(type));
  }
}

void PortTypeTest::undefined_toString_throws_exception()
{
  CPPUNIT_ASSERT_THROW(toString(PortType(-1)), std::invalid_argument);
}

void PortTypeTest::to_ostream_is_same_as_toString()
{
  for (PortType type : portTypeList()) {
    std::stringstream ss;
    ss << type;
    CPPUNIT_ASSERT_EQUAL(toString(type), ss.str());
  }
}

void PortTypeTest::undefined_to_ostream_throws_exception()
{
  std::stringstream ss;
  CPPUNIT_ASSERT_THROW(ss << PortType(-1), std::invalid_argument);
}

void PortTypeTest::signal_is_right()
{
  CPPUNIT_ASSERT_EQUAL(Side::Right, sideOf(PortType::Signal));
}

void PortTypeTest::slot_is_left()
{
  CPPUNIT_ASSERT_EQUAL(Side::Left, sideOf(PortType::Slot));
}

void PortTypeTest::sideOf_is_defined_for_all()
{
  for (PortType type : portTypeList()) {
    CPPUNIT_ASSERT_NO_THROW(sideOf(type));
  }
}

void PortTypeTest::undefined_sideOf_throws_exception()
{
  CPPUNIT_ASSERT_THROW(sideOf(PortType(-1)), std::invalid_argument);
}

void PortTypeTest::portTypeFromUint_matches_portTypeList_index()
{
  for (uint idx = 0; idx < portTypeList().size(); idx++) {
    PortType type = portTypeList()[idx];
    CPPUNIT_ASSERT_EQUAL(type, portTypeFromUint(idx));
  }
}

void PortTypeTest::undefined_portTypeFromUint_throws_exception()
{
  CPPUNIT_ASSERT_THROW(portTypeFromUint(10000000), std::out_of_range);
}

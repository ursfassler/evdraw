// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortTypeTest.hpp"

#include <core/component/PortType.hpp>
#include <core/types.hpp>
#include <core/util/stdlist.hpp>

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

void PortTypeTest::portTypeFromString_matches_toString_for_all()
{
  for (uint idx = 0; idx < portTypeList().size(); idx++) {
    const PortType type = portTypeList()[idx];
    const std::string string = toString(type);
    CPPUNIT_ASSERT_EQUAL(type, portTypeFromString(string));
  }
}

void PortTypeTest::undefined_portTypeFromString_throws_exception()
{
  CPPUNIT_ASSERT_THROW(portTypeFromString("no type"), std::invalid_argument);
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

void PortTypeTest::uintFromPortType_matches_portTypeList_index()
{
  for (uint idx = 0; idx < portTypeList().size(); idx++) {
    auto type = portTypeList()[idx];
    CPPUNIT_ASSERT_EQUAL(idx, uintFromPortType(type));
  }
}


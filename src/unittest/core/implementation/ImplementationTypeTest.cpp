// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ImplementationTypeTest.hpp"

#include <core/implementation/ImplementationType.hpp>
#include <core/util/list.hpp>

#include <vector>
#include <sstream>

void ImplementationTypeTest::implementationTypeList_contains_empty()
{
  const std::vector<ImplementationType> list = implementationTypeList();
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), ImplementationType::Empty));
}

void ImplementationTypeTest::implementationTypeList_contains_composition()
{
  const std::vector<ImplementationType> list = implementationTypeList();
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), ImplementationType::Composition));
}

void ImplementationTypeTest::empty_toString()
{
  CPPUNIT_ASSERT_EQUAL(std::string("empty"), toString(ImplementationType::Empty));
}

void ImplementationTypeTest::composition_toString()
{
  CPPUNIT_ASSERT_EQUAL(std::string("composition"), toString(ImplementationType::Composition));
}

void ImplementationTypeTest::toString_is_defined_for_all()
{
  for (ImplementationType type : implementationTypeList()) {
    CPPUNIT_ASSERT_NO_THROW(toString(type));
  }
}

void ImplementationTypeTest::undefined_toString_throws_exception()
{
  CPPUNIT_ASSERT_THROW(toString(ImplementationType(-1)), std::invalid_argument);
}

void ImplementationTypeTest::to_ostream_is_same_as_toString()
{
  for (ImplementationType type : implementationTypeList()) {
    std::stringstream ss;
    ss << type;
    CPPUNIT_ASSERT_EQUAL(toString(type), ss.str());
  }
}

void ImplementationTypeTest::undefined_to_ostream_throws_exception()
{
  std::stringstream ss;
  CPPUNIT_ASSERT_THROW(ss << ImplementationType(-1), std::invalid_argument);
}

void ImplementationTypeTest::implementationTypeFromUint_matches_implementationTypeList_index()
{
  for (uint idx = 0; idx < implementationTypeList().size(); idx++) {
    ImplementationType type = implementationTypeList()[idx];
    CPPUNIT_ASSERT_EQUAL(type, implementationTypeFromUint(idx));
  }
}

void ImplementationTypeTest::undefined_implementationTypeFromUint_throws_exception()
{
  CPPUNIT_ASSERT_THROW(implementationTypeFromUint(10000000), std::out_of_range);
}

void ImplementationTypeTest::uintFromImplementationType_matches_implementationTypeList_index()
{
  for (uint idx = 0; idx < implementationTypeList().size(); idx++) {
    ImplementationType type = implementationTypeList()[idx];
    CPPUNIT_ASSERT_EQUAL(idx, uintFromImplementationType(type));
  }
}

void ImplementationTypeTest::undefined_uintFromImplementationType_throws_exception()
{
  CPPUNIT_ASSERT_THROW(uintFromImplementationType(ImplementationType(-1)), std::invalid_argument);
}

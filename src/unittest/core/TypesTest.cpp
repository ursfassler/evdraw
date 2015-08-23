// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "TypesTest.hpp"

#include <core/types.hpp>

#include <sstream>
#include <string>

void TypesTest::printConnectorSideLeft()
{
  std::stringstream ss;
  ss << Side::Left;
  CPPUNIT_ASSERT_EQUAL(std::string("left"), ss.str());
}

void TypesTest::printConnectorSideRight()
{
  std::stringstream ss;
  ss << Side::Right;
  CPPUNIT_ASSERT_EQUAL(std::string("right"), ss.str());
}

void TypesTest::printVectorOfPaperUnit()
{
  std::stringstream ss;
  ss << std::vector<PaperUnit>({10, -10, 1, 42, 3});
  CPPUNIT_ASSERT_EQUAL(std::string("[10 -10 1 42 3]"), ss.str());
}

#include "TypesTest.hpp"

#include <core/types.hpp>

#include <sstream>
#include <string>

void TypesTest::printConnectorSideLeft()
{
  std::stringstream ss;
  ss << ConnectorSide::Left;
  CPPUNIT_ASSERT_EQUAL(std::string("left"), ss.str());
}

void TypesTest::printConnectorSideRight()
{
  std::stringstream ss;
  ss << ConnectorSide::Right;
  CPPUNIT_ASSERT_EQUAL(std::string("right"), ss.str());
}

void TypesTest::pointCreateArguments()
{
  Point point(30, 50);
  CPPUNIT_ASSERT_EQUAL(30, point.x);
  CPPUNIT_ASSERT_EQUAL(50, point.y);
}

void TypesTest::pointPrint()
{
  Point point(30,50);
  std::stringstream ss;
  ss << point;
  CPPUNIT_ASSERT_EQUAL(std::string("(30,50)"), ss.str());
}

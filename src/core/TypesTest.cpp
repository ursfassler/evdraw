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

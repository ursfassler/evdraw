#include "errorTest.hpp"

#include <core/util/error.hpp>

void errorTest::unreachableCode_throws_exception()
{
  CPPUNIT_ASSERT_THROW(unreachableCode(), std::runtime_error);
}

void errorTest::notYetImplemented_throws_exception()
{
  CPPUNIT_ASSERT_THROW(notYetImplemented(), std::runtime_error);
}

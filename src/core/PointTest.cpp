#include "PointTest.hpp"

#include "Point.hpp"

#include <sstream>

void PointTest::create()
{
  Point point(10,20);
  CPPUNIT_ASSERT_EQUAL(10, point.x);
  CPPUNIT_ASSERT_EQUAL(20, point.y);
}

void PointTest::print()
{
  Point point(10,20);
  std::stringstream ss;
  ss << point;
  CPPUNIT_ASSERT_EQUAL(std::string("(10,20)"), ss.str());
}

void PointTest::equal()
{
  CPPUNIT_ASSERT_EQUAL( true, Point(10,20) == Point(10,20));
  CPPUNIT_ASSERT_EQUAL(false, Point(11,20) == Point(10,20));
  CPPUNIT_ASSERT_EQUAL(false, Point(10,21) == Point(10,20));
}

void PointTest::notEqual()
{
  CPPUNIT_ASSERT_EQUAL(false, Point(10,20) != Point(10,20));
  CPPUNIT_ASSERT_EQUAL( true, Point(11,20) != Point(10,20));
  CPPUNIT_ASSERT_EQUAL( true, Point(10,21) != Point(10,20));
}

void PointTest::add()
{
  CPPUNIT_ASSERT_EQUAL(Point(0,0), Point(0,0) + Point(0,0));
  CPPUNIT_ASSERT_EQUAL(Point(40,60), Point(10,20) + Point(30,40));
  CPPUNIT_ASSERT_EQUAL(Point(-3,3), Point(-1,2) + Point(-2,1));
}


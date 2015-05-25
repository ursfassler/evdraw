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

void PointTest::plus()
{
  CPPUNIT_ASSERT_EQUAL(Point(0,0), Point(0,0) + Point(0,0));
  CPPUNIT_ASSERT_EQUAL(Point(40,60), Point(10,20) + Point(30,40));
  CPPUNIT_ASSERT_EQUAL(Point(-3,3), Point(-1,2) + Point(-2,1));
}

void PointTest::minus()
{
  CPPUNIT_ASSERT_EQUAL(Point(0,0), Point(0,0) - Point(0,0));
  CPPUNIT_ASSERT_EQUAL(Point(-20,-40), Point(10,20) - Point(30,60));
  CPPUNIT_ASSERT_EQUAL(Point(1,1), Point(-1,2) - Point(-2,1));
}

void PointTest::unaryMinus()
{
  CPPUNIT_ASSERT_EQUAL(Point(0,0), -Point(0,0));
  CPPUNIT_ASSERT_EQUAL(Point(-1,-2), -Point(1,2));
  CPPUNIT_ASSERT_EQUAL(Point(1,2), -Point(-1,-2));
}

void PointTest::divisionByScalar()
{
  CPPUNIT_ASSERT_EQUAL(Point(0,0), Point(0,0) / 2);
  CPPUNIT_ASSERT_EQUAL(Point(1,2), Point(10,20) / 10);
  CPPUNIT_ASSERT_EQUAL(Point(2,3), Point(5,7) / 2);
}


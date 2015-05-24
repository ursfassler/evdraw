#include "listTest.hpp"

#include "list.hpp"

#include <vector>
#include <string>
#include <stdexcept>

void ListTest::containsInt()
{
  std::vector<int>  list = { 1, 2, 3, 4, 5 };
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 1));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 2));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 3));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 4));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 5));
}

void ListTest::notContainsInt()
{
  std::vector<int>  list = { 1, 2, 3, 4, 5 };
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(), -2));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(), -1));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(),  0));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(),  6));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(),  7));
}

void ListTest::containsStringPointer()
{
  std::string hallo1 = "hallo";
  std::string hallo2 = "hallo";
  std::string hallo3 = "hallo";

  std::vector<std::string*>  list = { &hallo1, &hallo2, &hallo3 };

  CPPUNIT_ASSERT(contains(list.begin(), list.end(), &hallo1));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), &hallo2));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), &hallo3));
}

void ListTest::notContainsStringPointer()
{
  std::string hallo1 = "hallo";
  std::string hallo2 = "hallo";
  std::string hallo3 = "hallo";

  std::vector<std::string*>  list = { &hallo1, &hallo2 };

  CPPUNIT_ASSERT(!contains(list.begin(), list.end(), &hallo3));
}

void ListTest::indexOfInt()
{
  std::vector<int>  list = { 1, 2, 3, 4, 5 };
  CPPUNIT_ASSERT_EQUAL(size_t(0), indexOf(list.begin(), list.end(), 1));
  CPPUNIT_ASSERT_EQUAL(size_t(1), indexOf(list.begin(), list.end(), 2));
  CPPUNIT_ASSERT_EQUAL(size_t(2), indexOf(list.begin(), list.end(), 3));
  CPPUNIT_ASSERT_EQUAL(size_t(3), indexOf(list.begin(), list.end(), 4));
  CPPUNIT_ASSERT_EQUAL(size_t(4), indexOf(list.begin(), list.end(), 5));
}

void ListTest::noIndexOfInt()
{
  std::vector<int>  list = { 1, 2, 3, 4, 5 };
  CPPUNIT_ASSERT_THROW(indexOf(list.begin(), list.end(), 0), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(indexOf(list.begin(), list.end(), 42), std::invalid_argument);
}

void ListTest::indexOfStringPointer()
{
  std::string hallo1 = "hallo";
  std::string hallo2 = "hallo";
  std::string hallo3 = "hallo";

  std::vector<std::string*>  list = { &hallo1, &hallo2, &hallo3 };

  CPPUNIT_ASSERT_EQUAL(size_t(0), indexOf(list.begin(), list.end(), &hallo1));
  CPPUNIT_ASSERT_EQUAL(size_t(1), indexOf(list.begin(), list.end(), &hallo2));
  CPPUNIT_ASSERT_EQUAL(size_t(2), indexOf(list.begin(), list.end(), &hallo3));
}

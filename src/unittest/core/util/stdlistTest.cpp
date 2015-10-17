// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "stdlistTest.hpp"

#include <core/util/stdlist.hpp>

#include <vector>
#include <string>
#include <stdexcept>

void StdListTest::containsInt()
{
  std::vector<int>  list = { 1, 2, 3, 4, 5 };
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 1));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 2));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 3));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 4));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), 5));
}

void StdListTest::notContainsInt()
{
  std::vector<int>  list = { 1, 2, 3, 4, 5 };
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(), -2));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(), -1));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(),  0));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(),  6));
  CPPUNIT_ASSERT(!contains(list.begin(), list.end(),  7));
}

void StdListTest::containsStringPointer()
{
  std::string hallo1 = "hallo";
  std::string hallo2 = "hallo";
  std::string hallo3 = "hallo";

  std::vector<std::string*>  list = { &hallo1, &hallo2, &hallo3 };

  CPPUNIT_ASSERT(contains(list.begin(), list.end(), &hallo1));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), &hallo2));
  CPPUNIT_ASSERT(contains(list.begin(), list.end(), &hallo3));
}

void StdListTest::notContainsStringPointer()
{
  std::string hallo1 = "hallo";
  std::string hallo2 = "hallo";
  std::string hallo3 = "hallo";

  std::vector<std::string*>  list = { &hallo1, &hallo2 };

  CPPUNIT_ASSERT(!contains(list.begin(), list.end(), &hallo3));
}

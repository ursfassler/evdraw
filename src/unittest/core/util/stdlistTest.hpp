// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef STDLISTTEST_HPP
#define STDLISTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class StdListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( StdListTest );

    CPPUNIT_TEST(containsInt);
    CPPUNIT_TEST(notContainsInt);
    CPPUNIT_TEST(containsStringPointer);
    CPPUNIT_TEST(notContainsStringPointer);

    CPPUNIT_TEST_SUITE_END();

  public:
    void containsInt();
    void notContainsInt();
    void containsStringPointer();
    void notContainsStringPointer();

};

CPPUNIT_TEST_SUITE_REGISTRATION( StdListTest );

#endif

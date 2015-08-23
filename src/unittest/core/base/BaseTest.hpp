// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef BASETEST_HPP
#define BASETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class BaseTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( BaseTest );

    CPPUNIT_TEST(destructorIsVirtual);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructorIsVirtual();

};

CPPUNIT_TEST_SUITE_REGISTRATION( BaseTest );

#endif // BASETEST_HPP

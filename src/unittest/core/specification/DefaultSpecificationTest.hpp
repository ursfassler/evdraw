// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef DEFAULTSPECIFICATIONTEST_HPP
#define DEFAULTSPECIFICATIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DefaultSpecificationTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DefaultSpecificationTest );

    CPPUNIT_TEST(inheritsSpecification);
    CPPUNIT_TEST(orReturnsOrSpecification);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsSpecification();
    void orReturnsOrSpecification();

};

CPPUNIT_TEST_SUITE_REGISTRATION( DefaultSpecificationTest );

#endif // DEFAULTSPECIFICATIONTEST_HPP

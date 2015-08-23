// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ORSPECIFICATIONTEST_HPP
#define ORSPECIFICATIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class OrSpecificationTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( OrSpecificationTest );

    CPPUNIT_TEST(inheritsSpecification);

    CPPUNIT_TEST(noOredReturnFalse);
    CPPUNIT_TEST(addSpecTakesOwnership);
    CPPUNIT_TEST(addTrueReturnsTrue);

    CPPUNIT_TEST(addFalseReturnFalse);
    CPPUNIT_TEST(addFalseTrueReturnsTrue);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsSpecification();
    void takesLeft();
    void takesRight();
    void deletsLeftSpecInDestructor();
    void deletsRightSpecInDestructor();

    void noOredReturnFalse();
    void addSpecTakesOwnership();
    void addTrueReturnsTrue();

    void addFalseReturnFalse();
    void addFalseTrueReturnsTrue();
};

CPPUNIT_TEST_SUITE_REGISTRATION( OrSpecificationTest );

#endif // ORSPECIFICATIONTEST_HPP

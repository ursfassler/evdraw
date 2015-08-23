// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONTRACTTEST_HPP
#define CONTRACTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class contractTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( contractTest );

    CPPUNIT_TEST(throwPrecondition);
    CPPUNIT_TEST(noThrowPrecondition);
    CPPUNIT_TEST(throwPostcondition);
    CPPUNIT_TEST(noThrowPostcondition);
    CPPUNIT_TEST(throwInvariant);
    CPPUNIT_TEST(noThrowInvariant);

    CPPUNIT_TEST_SUITE_END();

  public:
    void throwPrecondition();
    void noThrowPrecondition();
    void throwPostcondition();
    void noThrowPostcondition();
    void throwInvariant();
    void noThrowInvariant();

};

CPPUNIT_TEST_SUITE_REGISTRATION( contractTest );


#endif // CONTRACTTEST_HPP

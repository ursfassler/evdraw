// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONTRACTTEST_HPP
#define CONTRACTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class contractTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( contractTest );

    CPPUNIT_TEST(throw_precondition);
    CPPUNIT_TEST(no_throw_precondition);
    CPPUNIT_TEST(precondition_message);

    CPPUNIT_TEST(throw_postcondition);
    CPPUNIT_TEST(no_throw_postcondition);
    CPPUNIT_TEST(postcondition_message);

    CPPUNIT_TEST(throw_invariant);
    CPPUNIT_TEST(no_throw_invariant);
    CPPUNIT_TEST(invariant_message);

    CPPUNIT_TEST_SUITE_END();

  public:
    void throw_precondition();
    void no_throw_precondition();
    void precondition_message();

    void throw_postcondition();
    void no_throw_postcondition();
    void postcondition_message();

    void throw_invariant();
    void no_throw_invariant();
    void invariant_message();

};

CPPUNIT_TEST_SUITE_REGISTRATION( contractTest );


#endif // CONTRACTTEST_HPP

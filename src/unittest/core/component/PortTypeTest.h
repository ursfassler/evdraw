// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTTYPETEST_H
#define PORTTYPETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class PortTypeTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PortTypeTest );

    CPPUNIT_TEST(portTypeList_contains_signal);
    CPPUNIT_TEST(portTypeList_contains_slot);

    CPPUNIT_TEST(signal_toString);
    CPPUNIT_TEST(slot_toString);
    CPPUNIT_TEST(toString_is_defined_for_all);
    CPPUNIT_TEST(undefined_toString_throws_exception);

    CPPUNIT_TEST(to_ostream_is_same_as_toString);
    CPPUNIT_TEST(undefined_to_ostream_throws_exception);

    CPPUNIT_TEST(signal_is_right);
    CPPUNIT_TEST(slot_is_left);
    CPPUNIT_TEST(sideOf_is_defined_for_all);
    CPPUNIT_TEST(undefined_sideOf_throws_exception);

    CPPUNIT_TEST(portTypeFromUint_matches_portTypeList_index);
    CPPUNIT_TEST(undefined_portTypeFromUint_throws_exception);

    CPPUNIT_TEST_SUITE_END();

  public:
    void portTypeList_contains_signal();
    void portTypeList_contains_slot();

    void signal_toString();
    void slot_toString();
    void toString_is_defined_for_all();
    void undefined_toString_throws_exception();

    void to_ostream_is_same_as_toString();
    void undefined_to_ostream_throws_exception();

    void signal_is_right();
    void slot_is_left();
    void sideOf_is_defined_for_all();
    void undefined_sideOf_throws_exception();

    void portTypeFromUint_matches_portTypeList_index();
    void undefined_portTypeFromUint_throws_exception();

};

CPPUNIT_TEST_SUITE_REGISTRATION( PortTypeTest );

#endif // PORTTYPETEST_H

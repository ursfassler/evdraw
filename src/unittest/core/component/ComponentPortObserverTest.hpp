// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTPORTOBSERVERTEST_HPP
#define COMPONENTPORTOBSERVERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentPortObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentPortObserverTest );

    CPPUNIT_TEST(destructor_is_virtual);
    CPPUNIT_TEST(inherits_ObserverCollection);

    CPPUNIT_TEST(get_informed_on_topIndex_change);
    CPPUNIT_TEST(do_not_inform_if_topIndex_is_the_same);

    CPPUNIT_TEST(get_informed_on_name_change);
    CPPUNIT_TEST(do_not_inform_if_name_is_the_same);

    CPPUNIT_TEST(get_informed_on_type_change);
    CPPUNIT_TEST(do_not_inform_if_type_is_the_same);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructor_is_virtual();
    void inherits_ObserverCollection();

    void get_informed_on_topIndex_change();
    void do_not_inform_if_topIndex_is_the_same();

    void get_informed_on_name_change();
    void do_not_inform_if_name_is_the_same();

    void get_informed_on_type_change();
    void do_not_inform_if_type_is_the_same();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentPortObserverTest );

#endif // COMPONENTPORTOBSERVERTEST_HPP

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTOBSERVERTEST_HPP
#define COMPONENTOBSERVERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentObserverTest );

    CPPUNIT_TEST(destructor_is_virtual);
    CPPUNIT_TEST(inherits_ObserverCollection);

    CPPUNIT_TEST(notify_nameChanged);
    CPPUNIT_TEST(do_not_notify_if_name_is_the_same);
    CPPUNIT_TEST(notify_heightChanged_on_addPort);
    CPPUNIT_TEST(notify_heightChanged_on_deletePort);
    CPPUNIT_TEST(notify_heightChanged_on_portTypeChange);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructor_is_virtual();
    void inherits_ObserverCollection();

    void notify_nameChanged();
    void do_not_notify_if_name_is_the_same();
    void notify_heightChanged_on_addPort();
    void notify_heightChanged_on_deletePort();
    void notify_heightChanged_on_portTypeChange();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentObserverTest );

#endif // COMPONENTOBSERVERTEST_H

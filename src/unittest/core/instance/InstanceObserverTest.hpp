// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEOBSERVERTEST_HPP
#define INSTANCEOBSERVERTEST_HPP

#include <core/instance/Instance.hpp>
#include <core/component/Component.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceObserverTest );

    CPPUNIT_TEST(destructorIsVirtual);
    CPPUNIT_TEST(inheritsObserverCollection);

    CPPUNIT_TEST(notifyAddPort);
    CPPUNIT_TEST(notifyDelPort);

    CPPUNIT_TEST(notify_setName);
    CPPUNIT_TEST(no_notify_when_set_same_name);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void destructorIsVirtual();
    void inheritsObserverCollection();

    void notifyAddPort();
    void notifyDelPort();

    void notify_setName();
    void no_notify_when_set_same_name();

  private:
    Component *component = nullptr;
    Instance *instance = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceObserverTest );

#endif // INSTANCEOBSERVERTEST_HPP

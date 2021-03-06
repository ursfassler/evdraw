// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEPORTOBSERVERTEST_HPP
#define INSTANCEPORTOBSERVERTEST_HPP

#include "InstanceMock.hpp"

#include <core/instance/InstancePort.hpp>
#include <core/component/ComponentPort.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstancePortObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstancePortObserverTest );

    CPPUNIT_TEST(destructor_is_virtual);
    CPPUNIT_TEST(inherits_ObserverCollection);

    CPPUNIT_TEST(notify_on_name_change);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void destructor_is_virtual();
    void inherits_ObserverCollection();

    void notify_on_name_change();

  private:
    ComponentPort *component = nullptr;
    InstanceMock *instance = nullptr;
    InstancePort *port = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstancePortObserverTest );

#endif // INSTANCEPORTOBSERVERTEST_HPP

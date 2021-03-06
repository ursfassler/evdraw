// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef OBSERVERTEST_HPP
#define OBSERVERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ObserverTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ObserverTest );

    CPPUNIT_TEST(addRemoveObserver);
    CPPUNIT_TEST(canNotRegisterNullptr);
    CPPUNIT_TEST(canNotUnregisterNullptr);
    CPPUNIT_TEST(canNotRegisterTwice);
    CPPUNIT_TEST(needToBeRegisteredToUnregister);

    CPPUNIT_TEST(virtualFunctionDispatch);

    CPPUNIT_TEST_SUITE_END();

  public:
    void addRemoveObserver();
    void canNotRegisterNullptr();
    void canNotUnregisterNullptr();
    void canNotRegisterTwice();
    void needToBeRegisteredToUnregister();

    void virtualFunctionDispatch();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ObserverTest );

#endif // OBSERVERTEST_HPP

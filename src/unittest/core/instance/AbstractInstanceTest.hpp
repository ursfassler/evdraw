// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ABSTRACTINSTANCETEST_HPP
#define ABSTRACTINSTANCETEST_HPP

#include <core/instance/AbstractInstance.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class AbstractInstanceTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( AbstractInstanceTest );

    CPPUNIT_TEST(destructorIsVirtual);
    CPPUNIT_TEST(inheritsVisitorClient);
    CPPUNIT_TEST(inheritsPosition);
    CPPUNIT_TEST(hasGetName);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void destructorIsVirtual();
    void inheritsVisitorClient();
    void inheritsPosition();
    void hasGetName();

  private:
    bool destroyed = false;
    AbstractInstance *instance = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( AbstractInstanceTest );

#endif // ABSTRACTINSTANCETEST_HPP

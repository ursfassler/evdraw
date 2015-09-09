// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTPORTTEST_HPP
#define COMPONENTPORTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentPortTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentPortTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(setTopIndex);

    CPPUNIT_TEST(setName);
    CPPUNIT_TEST(setType);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructor_is_virtual();
    void create();
    void setTopIndex();

    void setName();
    void setType();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentPortTest );

#endif // COMPONENTPORTTEST_HPP

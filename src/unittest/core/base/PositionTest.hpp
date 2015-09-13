// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef POSITIONTEST_HPP
#define POSITIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class PositionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PositionTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(absolutePosition);
    CPPUNIT_TEST(setOffset);

    CPPUNIT_TEST(setAbsolutePosition);

    CPPUNIT_TEST(notifyOnChange);
    CPPUNIT_TEST(notifyChildOnChange);
    CPPUNIT_TEST(notifyGrandchildOnChange);
    CPPUNIT_TEST(setAnchorUpdatesPosition);

    CPPUNIT_TEST(zeroPosition_get_singleton);
    CPPUNIT_TEST(zeroPosition_singleton_is_always_the_same);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void absolutePosition();
    void setOffset();

    void setAbsolutePosition();

    void notifyOnChange();
    void notifyChildOnChange();
    void notifyGrandchildOnChange();
    void setAnchorUpdatesPosition();

    void zeroPosition_get_singleton();
    void zeroPosition_singleton_is_always_the_same();
};

CPPUNIT_TEST_SUITE_REGISTRATION( PositionTest );

#endif

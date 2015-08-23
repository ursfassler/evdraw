// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTIONTEST_HPP
#define CONNECTIONTEST_HPP

#include <core/types.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ConnectionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(instanceStart);

    CPPUNIT_TEST(addHorizontalSegment);
    CPPUNIT_TEST(addVerticalSegment);
    CPPUNIT_TEST(addPoint);

    CPPUNIT_TEST(constructAndInsertSegment);
    CPPUNIT_TEST(insertSegmentAtSanePosition);

    CPPUNIT_TEST(notifyWhenAddVerticalSegment);
    CPPUNIT_TEST(notifyWhenAddHorizontalSegment);

    CPPUNIT_TEST(replaceStartPort);
    CPPUNIT_TEST(replaceEndPort);

    CPPUNIT_TEST(pathMinimal);
    CPPUNIT_TEST(pathLong);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void instanceStart();

    void addHorizontalSegment();
    void addVerticalSegment();
    void addPoint();

    void constructAndInsertSegment();
    void insertSegmentAtSanePosition();

    void notifyWhenAddVerticalSegment();
    void notifyWhenAddHorizontalSegment();

    void replaceStartPort();
    void replaceEndPort();

    void pathMinimal();
    void pathLong();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionTest );


#endif

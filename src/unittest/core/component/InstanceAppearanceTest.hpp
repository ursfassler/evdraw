// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEAPPEARANCETEST_HPP
#define INSTANCEAPPEARANCETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceAppearanceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceAppearanceTest );

    CPPUNIT_TEST(dimensionIsNotZero);
    CPPUNIT_TEST(heightDependsOnPorts);

    CPPUNIT_TEST(textHeightIsGreaterZero);

    CPPUNIT_TEST(portDimensionIsNotZero);
    CPPUNIT_TEST(portDimensionAsPoint);
    CPPUNIT_TEST(leftPortPositionMakesSense);
    CPPUNIT_TEST(rightPortPositionMakesSense);
    CPPUNIT_TEST(connectorOffsetMakesSense);

    CPPUNIT_TEST(portYOffset);

    CPPUNIT_TEST(leftPortXOffsetIsLeft);
    CPPUNIT_TEST(rightPortXOffsetIsRight);

    CPPUNIT_TEST_SUITE_END();

  public:
    void dimensionIsNotZero();
    void heightDependsOnPorts();

    void textHeightIsGreaterZero();

    void portDimensionIsNotZero();
    void portDimensionAsPoint();
    void leftPortPositionMakesSense();
    void rightPortPositionMakesSense();
    void connectorOffsetMakesSense();

    void portYOffset();

    void leftPortXOffsetIsLeft();
    void rightPortXOffsetIsRight();
};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceAppearanceTest );


#endif // INSTANCEAPPEARANCETEST_HPP

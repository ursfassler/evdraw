// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceAppearanceTest.hpp"

#include <core/component/InstanceAppearance.hpp>

void InstanceAppearanceTest::componentWidth_is_not_zero()
{
  CPPUNIT_ASSERT(InstanceAppearance::componentWidth() > 0);
}

void InstanceAppearanceTest::textHeightIsGreaterZero()
{
  CPPUNIT_ASSERT(InstanceAppearance::textHeight() > 0);
}

void InstanceAppearanceTest::portDimensionIsNotZero()
{
  CPPUNIT_ASSERT(InstanceAppearance::portWidth() > 0);
  CPPUNIT_ASSERT(InstanceAppearance::portHeight() > 0);
}

void InstanceAppearanceTest::portDimensionAsPoint()
{
  CPPUNIT_ASSERT_EQUAL(InstanceAppearance::portWidth(), InstanceAppearance::portDimension().x);
  CPPUNIT_ASSERT_EQUAL(InstanceAppearance::portHeight(), InstanceAppearance::portDimension().y);
}

void InstanceAppearanceTest::connectorOffsetMakesSense()
{
  CPPUNIT_ASSERT_EQUAL(InstanceAppearance::rightPortXOffset() + InstanceAppearance::portWidth()/2, InstanceAppearance::connectorOffset());
}

void InstanceAppearanceTest::portYOffset()
{
  CPPUNIT_ASSERT(InstanceAppearance::portVerticalOffset(0) > 0);
  CPPUNIT_ASSERT(InstanceAppearance::portVerticalOffset(1) > InstanceAppearance::portVerticalOffset(0));
  CPPUNIT_ASSERT(InstanceAppearance::portVerticalOffset(3) - InstanceAppearance::portVerticalOffset(2) == InstanceAppearance::portVerticalOffset(1) - InstanceAppearance::portVerticalOffset(0));
}

void InstanceAppearanceTest::leftPortXOffsetIsLeft()
{
  CPPUNIT_ASSERT(InstanceAppearance::leftPortXOffset() < 0);
}

void InstanceAppearanceTest::rightPortXOffsetIsRight()
{
  CPPUNIT_ASSERT(InstanceAppearance::rightPortXOffset() > 0);
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceAppearanceTest.hpp"

#include <core/component/Component.hpp>
#include <core/component/InstanceAppearance.hpp>
#include <core/component/ComponentFactory.hpp>

void InstanceAppearanceTest::dimensionIsNotZero()
{
  Component *component = ComponentFactory::produce("");
  CPPUNIT_ASSERT(InstanceAppearance::width() > 0);
  CPPUNIT_ASSERT(InstanceAppearance::height(*component) > 0);
  ComponentFactory::dispose(component);
}

void InstanceAppearanceTest::heightDependsOnPorts()
{
  Component *component = ComponentFactory::produce("");

  PaperUnit height0 = InstanceAppearance::height(*component);

  component->addPort(new ComponentPort("", PortType::Slot));
  PaperUnit height1 = InstanceAppearance::height(*component);

  component->addPort(new ComponentPort("", PortType::Slot));
  PaperUnit height2 = InstanceAppearance::height(*component);

  component->addPort(new ComponentPort("", PortType::Signal));
  PaperUnit height2a = InstanceAppearance::height(*component);

  component->addPort(new ComponentPort("", PortType::Signal));
  PaperUnit height2b = InstanceAppearance::height(*component);

  component->addPort(new ComponentPort("", PortType::Signal));
  PaperUnit height3 = InstanceAppearance::height(*component);

  CPPUNIT_ASSERT(height1 > height0);
  CPPUNIT_ASSERT(height2 > height1);
  CPPUNIT_ASSERT_EQUAL(height2, height2a);
  CPPUNIT_ASSERT_EQUAL(height2, height2b);
  CPPUNIT_ASSERT(height3 > height2);

  ComponentFactory::dispose(component);
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

void InstanceAppearanceTest::leftPortPositionMakesSense()
{
  CPPUNIT_ASSERT(InstanceAppearance::leftPortPosition(0).x < 0);
  CPPUNIT_ASSERT(InstanceAppearance::leftPortPosition(0).y > 0);
}

void InstanceAppearanceTest::rightPortPositionMakesSense()
{
  CPPUNIT_ASSERT(InstanceAppearance::rightPortPosition(0).x > 0);
  CPPUNIT_ASSERT(InstanceAppearance::rightPortPosition(0).y > 0);
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

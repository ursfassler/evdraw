#include "InstanceAppearanceTest.hpp"

#include <core/Component.hpp>
#include <core/InstanceAppearance.hpp>

void InstanceAppearanceTest::dimensionIsNotZero()
{
  Component component;
  InstanceAppearance appearance(&component);

  CPPUNIT_ASSERT(appearance.width() > 0);
  CPPUNIT_ASSERT(appearance.height() > 0);
}

void InstanceAppearanceTest::widthIsConstant()
{
  Component component;
  InstanceAppearance appearance(&component);

  PaperUnit originalWidth = appearance.width();

  component.addPortLeft(new ComponentPort(""));
  CPPUNIT_ASSERT_EQUAL(originalWidth, appearance.width());

  component.addPortLeft(new ComponentPort(""));
  CPPUNIT_ASSERT_EQUAL(originalWidth, appearance.width());

  component.addPortRight(new ComponentPort(""));
  CPPUNIT_ASSERT_EQUAL(originalWidth, appearance.width());
}

void InstanceAppearanceTest::heightDependsOnPorts()
{
  Component component;
  InstanceAppearance appearance(&component);

  PaperUnit height0 = appearance.height();

  component.addPortLeft(new ComponentPort(""));
  PaperUnit height1 = appearance.height();

  component.addPortLeft(new ComponentPort(""));
  PaperUnit height2 = appearance.height();

  component.addPortRight(new ComponentPort(""));
  PaperUnit height2a = appearance.height();

  component.addPortRight(new ComponentPort(""));
  PaperUnit height2b = appearance.height();

  component.addPortRight(new ComponentPort(""));
  PaperUnit height3 = appearance.height();

  CPPUNIT_ASSERT(height1 > height0);
  CPPUNIT_ASSERT(height2 > height1);
  CPPUNIT_ASSERT_EQUAL(height2, height2a);
  CPPUNIT_ASSERT_EQUAL(height2, height2b);
  CPPUNIT_ASSERT(height3 > height2);
}

void InstanceAppearanceTest::portDimensionIsNotZero()
{
  Component component;
  InstanceAppearance appearance(&component);

  CPPUNIT_ASSERT(appearance.portWidth() > 0);
  CPPUNIT_ASSERT(appearance.portHeight() > 0);
}

void InstanceAppearanceTest::portWidthIsConstant()
{
  Component component;
  InstanceAppearance appearance(&component);
  ComponentPort *port1 = new ComponentPort("");
  ComponentPort *port2 = new ComponentPort("");
  ComponentPort *port3 = new ComponentPort("");

  PaperUnit portWidth = appearance.portWidth();

  component.addPortLeft(port1);
  CPPUNIT_ASSERT_EQUAL(portWidth, appearance.portWidth());

  component.addPortLeft(port2);
  CPPUNIT_ASSERT_EQUAL(portWidth, appearance.portWidth());

  component.addPortRight(port3);
  CPPUNIT_ASSERT_EQUAL(portWidth, appearance.portWidth());

  CPPUNIT_ASSERT_EQUAL(portWidth, appearance.portWidth());
}

void InstanceAppearanceTest::portHeightIsConstant()
{
  Component component;
  InstanceAppearance appearance(&component);
  ComponentPort *port1 = new ComponentPort("");
  ComponentPort *port2 = new ComponentPort("");
  ComponentPort *port3 = new ComponentPort("");

  PaperUnit height = appearance.portHeight();

  component.addPortLeft(port1);
  CPPUNIT_ASSERT_EQUAL(height, appearance.portHeight());

  component.addPortLeft(port2);
  CPPUNIT_ASSERT_EQUAL(height, appearance.portHeight());

  component.addPortRight(port3);
  CPPUNIT_ASSERT_EQUAL(height, appearance.portHeight());
}

void InstanceAppearanceTest::leftPortXOffset()
{
  Component component;
  InstanceAppearance appearance(&component);

  CPPUNIT_ASSERT(appearance.leftPortXOffset() < 0);
}

void InstanceAppearanceTest::leftPortYOffset()
{
  Component component;
  ComponentPort *port = new ComponentPort("");
  component.addPortLeft(port);

  InstanceAppearance appearance(&component);

  CPPUNIT_ASSERT(appearance.leftPortYOffset(port) > 0);
}

void InstanceAppearanceTest::rightPortXOffset()
{
  Component component;
  InstanceAppearance appearance(&component);

  CPPUNIT_ASSERT(appearance.rightPortXOffset() > 0);
}

void InstanceAppearanceTest::rightPortYOffset()
{
  Component component;
  ComponentPort *port = new ComponentPort("");
  component.addPortRight(port);

  InstanceAppearance appearance(&component);

  CPPUNIT_ASSERT(appearance.rightPortYOffset(port) > 0);
}

#include "InstanceAppearanceTest.hpp"

#include "Component.hpp"
#include "InstanceAppearance.hpp"
#include "ComponentFactory.hpp"

void InstanceAppearanceTest::dimensionIsNotZero()
{
  Component component("");
  CPPUNIT_ASSERT(InstanceAppearance::width() > 0);
  CPPUNIT_ASSERT(InstanceAppearance::height(component) > 0);
}

void InstanceAppearanceTest::heightDependsOnPorts()
{
  Component component("");

  PaperUnit height0 = InstanceAppearance::height(component);

  component.addPortLeft(new ComponentPort(""));
  PaperUnit height1 = InstanceAppearance::height(component);

  component.addPortLeft(new ComponentPort(""));
  PaperUnit height2 = InstanceAppearance::height(component);

  component.addPortRight(new ComponentPort(""));
  PaperUnit height2a = InstanceAppearance::height(component);

  component.addPortRight(new ComponentPort(""));
  PaperUnit height2b = InstanceAppearance::height(component);

  component.addPortRight(new ComponentPort(""));
  PaperUnit height3 = InstanceAppearance::height(component);

  CPPUNIT_ASSERT(height1 > height0);
  CPPUNIT_ASSERT(height2 > height1);
  CPPUNIT_ASSERT_EQUAL(height2, height2a);
  CPPUNIT_ASSERT_EQUAL(height2, height2b);
  CPPUNIT_ASSERT(height3 > height2);

  ComponentFactory::cleanup(component);
}

void InstanceAppearanceTest::portDimensionIsNotZero()
{
  CPPUNIT_ASSERT(InstanceAppearance::portWidth() > 0);
  CPPUNIT_ASSERT(InstanceAppearance::portHeight() > 0);
}

void InstanceAppearanceTest::portYOffset()
{
  CPPUNIT_ASSERT(InstanceAppearance::portYOffset(0) > 0);
  CPPUNIT_ASSERT(InstanceAppearance::portYOffset(1) > InstanceAppearance::portYOffset(0));
  CPPUNIT_ASSERT(InstanceAppearance::portYOffset(3) - InstanceAppearance::portYOffset(2) == InstanceAppearance::portYOffset(1) - InstanceAppearance::portYOffset(0));
}

void InstanceAppearanceTest::leftPortXOffsetIsLeft()
{
  CPPUNIT_ASSERT(InstanceAppearance::leftPortXOffset() < 0);
}

void InstanceAppearanceTest::rightPortXOffsetIsRight()
{
  CPPUNIT_ASSERT(InstanceAppearance::rightPortXOffset() > 0);
}

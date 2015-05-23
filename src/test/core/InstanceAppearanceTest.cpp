#include "InstanceAppearanceTest.hpp"

#include <core/Component.hpp>
#include <core/InstanceAppearance.hpp>

void InstanceAppearanceTest::dimension()
{
  Component component;
  InstanceAppearance appearance(&component);

  CPPUNIT_ASSERT(appearance.width() > 0);
  CPPUNIT_ASSERT(appearance.height() > 0);
}

void InstanceAppearanceTest::width()
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

void InstanceAppearanceTest::height()
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

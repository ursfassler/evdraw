#ifndef INSTANCEAPPEARANCETEST_HPP
#define INSTANCEAPPEARANCETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceAppearanceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceAppearanceTest );

    CPPUNIT_TEST(dimensionIsNotZero);
    CPPUNIT_TEST(heightDependsOnPorts);

    CPPUNIT_TEST(portDimensionIsNotZero);

    CPPUNIT_TEST(portYOffset);

    CPPUNIT_TEST(leftPortXOffsetIsLeft);
    CPPUNIT_TEST(rightPortXOffsetIsRight);

    CPPUNIT_TEST_SUITE_END();

  public:
    void dimensionIsNotZero();
    void heightDependsOnPorts();

    void portDimensionIsNotZero();

    void portYOffset();

    void leftPortXOffsetIsLeft();
    void rightPortXOffsetIsRight();
};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceAppearanceTest );


#endif // INSTANCEAPPEARANCETEST_HPP

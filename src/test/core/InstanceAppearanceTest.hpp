#ifndef INSTANCEAPPEARANCETEST_HPP
#define INSTANCEAPPEARANCETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceAppearanceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceAppearanceTest );

    CPPUNIT_TEST(dimensionIsNotZero);
    CPPUNIT_TEST(widthIsConstant);
    CPPUNIT_TEST(heightDependsOnPorts);

    CPPUNIT_TEST(portDimensionIsNotZero);
    CPPUNIT_TEST(portWidthIsConstant);
    CPPUNIT_TEST(portHeightIsConstant);

    CPPUNIT_TEST(leftPortXOffset);
    CPPUNIT_TEST(leftPortYOffset);
    CPPUNIT_TEST(rightPortXOffset);
    CPPUNIT_TEST(rightPortYOffset);

    CPPUNIT_TEST_SUITE_END();

  public:
    void dimensionIsNotZero();
    void widthIsConstant();
    void heightDependsOnPorts();

    void portDimensionIsNotZero();
    void portWidthIsConstant();
    void portHeightIsConstant();

    void leftPortXOffset();
    void leftPortYOffset();
    void rightPortXOffset();
    void rightPortYOffset();
};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceAppearanceTest );


#endif // INSTANCEAPPEARANCETEST_HPP

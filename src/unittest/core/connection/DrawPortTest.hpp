#ifndef DRAWPORTTEST_HPP
#define DRAWPORTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DrawPortTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DrawPortTest );

    CPPUNIT_TEST(inheritsAbstractPort);
    CPPUNIT_TEST(inheritsPosition);

    CPPUNIT_TEST(getAnchorPosition);
    CPPUNIT_TEST(getInformedByPositionChange);

    CPPUNIT_TEST(getName);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsAbstractPort();
    void inheritsPosition();

    void getAnchorPosition();
    void getInformedByPositionChange();

    void getName();

};

CPPUNIT_TEST_SUITE_REGISTRATION( DrawPortTest );

#endif // DRAWPORTTEST_HPP

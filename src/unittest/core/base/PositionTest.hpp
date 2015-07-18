#ifndef POSITIONTEST_HPP
#define POSITIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class PositionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PositionTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(inheritsBase);
    CPPUNIT_TEST(absolutePosition);
    CPPUNIT_TEST(setOffset);

    CPPUNIT_TEST(setAbsolutePosition);

    CPPUNIT_TEST(notifyOnChange);
    CPPUNIT_TEST(notifyChildOnChange);
    CPPUNIT_TEST(notifyGrandchildOnChange);
    CPPUNIT_TEST(setAnchorUpdatesPosition);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void inheritsBase();
    void absolutePosition();
    void setOffset();

    void setAbsolutePosition();

    void notifyOnChange();
    void notifyChildOnChange();
    void notifyGrandchildOnChange();
    void setAnchorUpdatesPosition();
};

CPPUNIT_TEST_SUITE_REGISTRATION( PositionTest );

#endif

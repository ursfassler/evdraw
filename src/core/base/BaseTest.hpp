#ifndef BASETEST_HPP
#define BASETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class BaseTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( BaseTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(absolutePosition);
    CPPUNIT_TEST(setOffset);

    CPPUNIT_TEST(notifyOnChange);
    CPPUNIT_TEST(notifyChildOnChange);
    CPPUNIT_TEST(notifyGrandchildOnChange);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void absolutePosition();
    void setOffset();

    void notifyOnChange();
    void notifyChildOnChange();
    void notifyGrandchildOnChange();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BaseTest );

#endif // BASETEST_HPP

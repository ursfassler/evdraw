#ifndef CONNECTIONTEST_HPP
#define CONNECTIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class ConnectionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(addHorizontalSegment);
    CPPUNIT_TEST(addVerticalSegment);
    CPPUNIT_TEST(addIntermediatePoint);

    CPPUNIT_TEST(interactveCreateConnection);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void addHorizontalSegment();
    void addVerticalSegment();
    void addIntermediatePoint();

    void interactveCreateConnection();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionTest );


#endif

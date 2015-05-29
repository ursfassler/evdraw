#ifndef CONNECTIONTEST_HPP
#define CONNECTIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class ConnectionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionTest );

    CPPUNIT_TEST(createFinished);
    CPPUNIT_TEST(createBuild);

    CPPUNIT_TEST(addHorizontalSegment);
    CPPUNIT_TEST(addVerticalSegment);
    CPPUNIT_TEST(addIntermediatePoint);

    CPPUNIT_TEST(buildToEndAndAddSegment);
    CPPUNIT_TEST(buildToEndAndFinish);
    CPPUNIT_TEST(buildToEndAddAndFinish);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createFinished();
    void createBuild();

    void addHorizontalSegment();
    void addVerticalSegment();
    void addIntermediatePoint();

    void buildToEndAndAddSegment();
    void buildToEndAndFinish();
    void buildToEndAddAndFinish();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionTest );


#endif

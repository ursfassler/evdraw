#ifndef RIZZLYPRINTTEST_HPP
#define RIZZLYPRINTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class RizzlyPrintTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( RizzlyPrintTest );

    CPPUNIT_TEST(printEmpty);
    CPPUNIT_TEST(onlyInstance);
    CPPUNIT_TEST(connection);

    CPPUNIT_TEST_SUITE_END();

  public:
    void printEmpty();
    void onlyInstance();
    void connection();
};

CPPUNIT_TEST_SUITE_REGISTRATION( RizzlyPrintTest );


#endif // RIZZLYPRINTTEST_HPP

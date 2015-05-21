#ifndef CONNECTIONTEST_HPP
#define CONNECTIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class ConnectionTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionTest );

    CPPUNIT_TEST(createEmptyConnection);
    CPPUNIT_TEST(createInvalidConnection);
    CPPUNIT_TEST(createConnection);
    CPPUNIT_TEST(createDiagonalConnection);
    CPPUNIT_TEST(createPathConnection);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createEmptyConnection();
    void createInvalidConnection();
    void createConnection();
    void createDiagonalConnection();
    void createPathConnection();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionTest );


#endif

#ifndef CONNECTIONFACTORYTEST_HPP
#define CONNECTIONFACTORYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class ConnectionFactoryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionFactoryTest );

    CPPUNIT_TEST(cleanup);
    CPPUNIT_TEST(canNotDisposeNullptr);
    CPPUNIT_TEST(createEmptyConnection);
    CPPUNIT_TEST(createInvalidConnection);
    CPPUNIT_TEST(createConnection);
    CPPUNIT_TEST(createDiagonalConnection);
    CPPUNIT_TEST(createPathConnection);

    CPPUNIT_TEST(createConstructionConnection);
    CPPUNIT_TEST(createConnectionFromConstruction);
    CPPUNIT_TEST(createLongerConnectionFromConstruction);

    CPPUNIT_TEST_SUITE_END();

  public:
    void cleanup();
    void canNotDisposeNullptr();
    void createEmptyConnection();
    void createInvalidConnection();
    void createConnection();
    void createDiagonalConnection();
    void createPathConnection();

    void createConstructionConnection();
    void createConnectionFromConstruction();
    void createLongerConnectionFromConstruction();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionFactoryTest );


#endif

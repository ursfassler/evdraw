#ifndef CONNECTIONFACTORYTEST_HPP
#define CONNECTIONFACTORYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class ConnectionFactoryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionFactoryTest );

    CPPUNIT_TEST(createPointListWithOnlyOneElement);
    CPPUNIT_TEST(createMinimalPointList);
    CPPUNIT_TEST(createSimplePointList);

    CPPUNIT_TEST(cleanup);
    CPPUNIT_TEST(canNotDisposeNullptr);
    CPPUNIT_TEST(createEmptyConnection);
    CPPUNIT_TEST(createInvalidConnection);
    CPPUNIT_TEST(createConnection);
    CPPUNIT_TEST(createPathConnection);
    CPPUNIT_TEST(createConstruction);

    CPPUNIT_TEST(connectionIsRegisteredAtStartPort);
    CPPUNIT_TEST(connectionIsRegisteredAtEndPort);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createPointListWithOnlyOneElement();
    void createMinimalPointList();
    void createSimplePointList();

    void cleanup();
    void canNotDisposeNullptr();
    void createEmptyConnection();
    void createInvalidConnection();
    void createConnection();
    void createPathConnection();
    void createConstruction();

    void connectionIsRegisteredAtStartPort();
    void connectionIsRegisteredAtEndPort();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionFactoryTest );


#endif

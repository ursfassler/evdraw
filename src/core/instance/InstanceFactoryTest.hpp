#ifndef INSTANCEFACTORYTEST_HPP
#define INSTANCEFACTORYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceFactoryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceFactoryTest );

    CPPUNIT_TEST(componentCanNotBeNullptr);
    CPPUNIT_TEST(canNotDisposeNullptr);
    CPPUNIT_TEST(cleanupRemovesInput);
    CPPUNIT_TEST(produceSimple);
    CPPUNIT_TEST(produceWithPorts);
    CPPUNIT_TEST(rightConnectorIsAtCorrectPosition);
    CPPUNIT_TEST(leftConnectorIsAtCorrectPosition);

    CPPUNIT_TEST_SUITE_END();

  public:
    void componentCanNotBeNullptr();
    void canNotDisposeNullptr();
    void cleanupRemovesInput();
    void produceSimple();
    void produceWithPorts();
    void rightConnectorIsAtCorrectPosition();
    void leftConnectorIsAtCorrectPosition();
};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceFactoryTest );

#endif // INSTANCEFACTORYTEST_HPP

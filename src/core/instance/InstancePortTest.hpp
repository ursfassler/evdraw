#ifndef INSTANCEPORTTEST_HPP
#define INSTANCEPORTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstancePortTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstancePortTest );

    CPPUNIT_TEST(createPort);
    CPPUNIT_TEST(offset);
    CPPUNIT_TEST(absolutePosition);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createPort();
    void offset();
    void absolutePosition();

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstancePortTest );

#endif // INSTANCEPORTTEST_HPP

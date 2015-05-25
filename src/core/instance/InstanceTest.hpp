#ifndef INSTANCETEST_HPP
#define INSTANCETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceTest );

    CPPUNIT_TEST(produce);
    CPPUNIT_TEST(setPosition);
    CPPUNIT_TEST(inheritsBase);

    CPPUNIT_TEST(addInputPort);
    CPPUNIT_TEST(addOutputPort);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();
    void setPosition();
    void inheritsBase();

    void addInputPort();
    void addOutputPort();
};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceTest );

#endif // INSTANCETEST_HPP

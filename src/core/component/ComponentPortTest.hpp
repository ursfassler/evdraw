#ifndef COMPONENTPORTTEST_HPP
#define COMPONENTPORTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentPortTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentPortTest );

    CPPUNIT_TEST(produce);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();


};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentPortTest );

#endif // COMPONENTPORTTEST_HPP

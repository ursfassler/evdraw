#ifndef COMPONENTFACTORYTEST_HPP
#define COMPONENTFACTORYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentFactoryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentFactoryTest );

    CPPUNIT_TEST(produce);
    CPPUNIT_TEST(canNotDisposeNullptr);
    CPPUNIT_TEST(cleanupComponentOnStack);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();
    void canNotDisposeNullptr();
    void cleanupComponentOnStack();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentFactoryTest );


#endif // COMPONENTFACTORYTEST_HPP

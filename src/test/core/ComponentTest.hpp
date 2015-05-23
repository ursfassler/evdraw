#ifndef COMPONENTTEST_HPP
#define COMPONENTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentTest );

    CPPUNIT_TEST(produce);

    CPPUNIT_TEST(addPortLeft);
    CPPUNIT_TEST(addPortRight);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();

    void addPortLeft();
    void addPortRight();


};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentTest );

#endif // COMPONENTTEST_HPP

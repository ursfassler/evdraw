#ifndef NULLIMPLEMENTATIONTEST_HPP
#define NULLIMPLEMENTATIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class NullImplementationTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( NullImplementationTest );

    CPPUNIT_TEST(construct);
    CPPUNIT_TEST(inheritsAbstractImplementation);

    CPPUNIT_TEST_SUITE_END();

  public:
    void construct();
    void inheritsAbstractImplementation();

};

CPPUNIT_TEST_SUITE_REGISTRATION( NullImplementationTest );

#endif // NULLIMPLEMENTATIONTEST_HPP

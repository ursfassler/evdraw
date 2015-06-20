#ifndef ABSTRACTIMPLEMENTATIONTEST_HPP
#define ABSTRACTIMPLEMENTATIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class AbstractImplementationTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( AbstractImplementationTest );

    CPPUNIT_TEST(destructorIsVirtual);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructorIsVirtual();

};

CPPUNIT_TEST_SUITE_REGISTRATION( AbstractImplementationTest );

#endif // ABSTRACTIMPLEMENTATIONTEST_HPP
